#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x83, 0x04};
IPAddress ip(10, 10, 142, 4);
IPAddress gw(10, 10, 142, 254);
IPAddress sn(255, 255, 255, 0);

EthernetServer server(80);

String opcaoInformada = "";
boolean statusLED = false;

const int LED = 7;

void setup() {
Ethernet.begin(mac, ip, gw, sn);
server.begin();

Serial.begin(9600);
Serial.print("Servidor rodando em:");
Serial.print(Ethernet.localIP());

}

void loop() {

EthernetClient client = server.available();


  if (client) {
    while (client.connected()) {
      if (client.available()) {

        char c = client.read();
        if (c != '\n') {
          opcaoInformada.concat(c);
          continue;
        }

        if (opcaoInformada.indexOf("?led=") > -1) {
          if (opcaoInformada.indexOf("?led=acender") > -1) {
            statusLED = true;
          } else {
            statusLED = false;
          }
        }
        
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type: text/html");
        client.println();
        String  html = "<html>";
                html += "<head><title>Teste Arduino</title></head>";
                html += "<body>";
                html += "<form method='get'>";
                html += "<select name='led'>";
                html += "<option>acender</option>";
                html += "<option>apagar</option>";
                html += "</select>";
                html += "<input type='submit' value='Enviar' />";
                html += "</form></body></html>";
        client.println(html); 
        client.stop();
  
        opcaoInformada = "";      
      } //if
    } //while
  } //if

  if (statusLED) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }


}
