// Ver 1.00
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

/* Set these to your desired credentials. */
const char APName[] = "********";
const char APPass[] = "12345678";      // 8 charctor

#define  MAX_CONNECT     2
boolean alreadyConnected[MAX_CONNECT] ;
WiFiServer server(23);
WiFiClient client[MAX_CONNECT];


void setup()
{
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.println("Program Start");

   WiFi.softAPConfig(IPAddress(192, 168, 0, 1),              // ip
                          IPAddress(192, 168, 0, 1),        // gateway
                           IPAddress(255, 255, 255, 0)  );  //sub net mask
   
   WiFi.softAP((char *)&APName[0] , APPass );

    delay(100);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin(); 
    Serial.println("\nServer Started.");
}

void loop()
{
    unsigned int i;
    for (i= 0; i<MAX_CONNECT; i++)
    {
        // wait for a new client:
        if (!client[i])
        {
            client[i] = server.available();
#if 0
            if(client[i])
                Serial.print("\nConnection open trg \n"  );
#endif
        }
        else
        {
            if (client[i].status() == CLOSED)
            {
                client[i].stop();
                Serial.print("\nConnection closed on client: "  );
                Serial.println(i);
                alreadyConnected[i] = false;
            }

            else
            {
                if(!alreadyConnected[i]) // when the client sends the first byte, say hello:
                {
                    Serial.print("Find Client:");
                    Serial.println(i);
                    client[i].println("Hello, client !");
                    alreadyConnected[i] = true;
                }

                if (client[i].available())
                {
                    String data = client[i].readString();
                    client[i].print(data);
                    Serial.println(data);
                }
            }
        }
    }
}
