/*
  MySQL Connector/Arduino Example : query with PROGMEM strings

  This example demonstrates how to issue queries using strings stored in
  PROGMEM. As you will see, you need only add a parameter to the execute()
  method in the cursor class, const and PROGMEM to the string declaration
  and add the #include <avr/pgmspace.h> directive.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  NOTICE: You must download and install the World sample database to run
          this sketch unaltered. See http://dev.mysql.com/doc/index-other.html.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Connect a USB cable to your Arduino
  4) Select the correct board and port
  5) Compile and upload the sketch to your Arduino
  6) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  Note: The MAC address can be anything so long as it is unique on your network.

  Created by: Dr. Charles A. Bell
*/
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <avr/pgmspace.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(10,0,1,35);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "secret";        // MySQL user login password

// Sample query
const char PROGMEM query[] = "SELECT * FROM world.city LIMIT 12";

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
}


void loop() {
  delay(2000);

  Serial.println("\nRunning SELECT from PROGMEM and printing results\n");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query with the PROGMEM option
  cur_mem->execute(query, true);
  // Show the results
  cur_mem->show_results();
  // Deleting the cursor also frees up memory used
  delete cur_mem;
}
