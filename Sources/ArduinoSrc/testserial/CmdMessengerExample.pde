// This example demonstrates CmdMessenger's callback  & attach methods
// For Arduino Uno and Arduino Duemilanove board (may work with other)

// Download these into your Sketches/libraries/ folder...

// CmdMessenger library available from https://github.com/dreamcat4/cmdmessenger
#include <CmdMessenger.h>

// Base64 library available from https://github.com/adamvr/arduino-base64
#include <Base64.h>

// Streaming4 library available from http://arduiniana.org/libraries/streaming/
#include <Streaming.h>

// Mustnt conflict / collide with our message payload data. Fine if we use base64 library ^^ above
char field_separator = ',';
char command_separator = ';';

// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);


// ------------------ S E R I A L  M O N I T O R -----------------------------
// 
// Try typing these command messages in the serial monitor!
// 
// 4,hi,heh,ho!;
// 5;
// 5,dGhlIGJlYXJzIGFyZSBhbGxyaWdodA==;
// 5,dGhvc2UgbmFzdHkgY29udHJvbCA7OyBjaGFyYWN0ZXJzICws==;
// 2;
// 6;
// 
// 
// Expected output:
// 
// 1,Arduino ready;
// 1,bens cmd recieved;
// 1,hi;
// 1,heh;
// 1,ho!;
// 1,jerrys cmd recieved;
// 1,"the bears are allright" encoded in base64...;
// 1,dGhlIGJlYXJzIGFyZSBhbGxyaWdodA==;
// 1,jerrys cmd recieved;
// 1,what you send me, decoded base64...;
// 1,the bears are allright;
// 1,jerrys cmd recieved;
// 1,what you send me, decoded base64...;
// 1,those nasty control ;; characters ,,;
// 1,Arduino ready;
// 3,Unknown command;
// 


// ------------------ C M D  L I S T I N G ( T X / R X ) ---------------------

enum
{
  StartedCmd = 7,
  StopedCmd = 8,
  AlertCmd = 9
};

// We can define up to a default of 50 cmds total, including both directions (send + recieve)
// and including also the first 4 default command codes for the generic error handling.
// If you run out of message slots, then just increase the value of MAXCALLBACKS in CmdMessenger.h

// Commands we send from the Arduino to be received on the PC
enum
{
  kCOMM_ERROR    = 000, // Lets Arduino report serial port comm error back to the PC (only works for some comm errors)
  kACK           = 001, // Arduino acknowledges cmd was received
  kARDUINO_READY = 002, // After opening the comm port, send this cmd 02 from PC to check arduino is ready
  kERR           = 003, // Arduino reports badly formatted cmd, or cmd not recognised

  // Now we can define many more 'send' commands, coming from the arduino -> the PC, eg
  // kICE_CREAM_READY,
  // kICE_CREAM_PRICE,
  // For the above commands, we just call cmdMessenger.sendCmd() anywhere we want in our Arduino program.

  kSEND_CMDS_END, // Mustnt delete this line
};

// Commands we send from the PC and want to recieve on the Arduino.
// We must define a callback function in our Arduino program for each entry in the list below vv.
// They start at the address kSEND_CMDS_END defined ^^ above as 004
messengerCallbackFunction messengerCallbacks[] = 
{
  Start,            // 004 in this example
  Stop,  // 005
  EmergencyStop, // 006
  NULL
};
// Its also possible (above ^^) to implement some symetric commands, when both the Arduino and
// PC / host are using each other's same command numbers. However we recommend only to do this if you
// really have the exact same messages going in both directions. Then specify the integers (with '=')


// ------------------ C A L L B A C K  M E T H O D S -------------------------

void Start()
{
  // Message data is any ASCII bytes (0-255 value). But can't contain the field
  // separator, command separator chars you decide (eg ',' and ';')
  String inputData;
  while ( cmdMessenger.available() )
  {
    char buf[350] = { '\0' };
    cmdMessenger.copyString(buf, 350);
    inputData = inputData + String(buf);
  }
  if(!inputData.lenght())
  {
    cmdMessenger.sendCmd(kERR,"Start command is  empty");
    return;
  }
  int count = countSplitCharacters(inputData, field_separator);
  int array[count];
  int lastIndex = 0;
  int currentIndex = 0;
  for(int i = 0; i < count; i++){
    currentIndex = inputData.indexOf(field_separator,lastIndex);
    if(curentIndex == -1){
      break;
    }
    char charId[16];
    String strId = inputData.substring(lastIndex,currentIndex);
    if(strId.lenght() == 0 || strId.lenght() >= 16){
      break;
    }
    strId.toCharArray(charId,16);
    int id = atoi(charId);
    array[i] = id;
    lastIndex = currentIndex + 1;
  }
  
  for(int i = 0 ; i < count; i++){
    StatrtObject(array[i]);
    Started(array[i]);
  }
  
}

void Stop()
{
  // To avoid conflicts with the control characters and any newline characters
  // Message length increases about 30%-40%

  while ( cmdMessenger.available() )
  {
    
  }

}

void EmergencyStop()
{
}

void Started(int id)
{
  char chId [16];
  String strId = String(id);
  strId.toCharArray(chId,16);
  cmdMessenger.sendCmd(StartedCmd,chId);
}

void Stoped(int id)
{
  char chId [16];
  String strId = String(id);
  strId.toCharArray(chId,16);
  cmdMessenger.sendCmd(StopedCmd,chId);

}

void Alert()
{}

void StartObject(int id)
{
  delay(5000);
}


// ------------------ D E F A U L T  C A L L B A C K S -----------------------

void arduino_ready()
{
  // In response to ping. We just send a throw-away Acknowledgement to say "im alive"
  cmdMessenger.sendCmd(kACK,"Arduino ready");
}

void unknownCmd()
{
  // Default response for unknown commands and corrupt messages
  cmdMessenger.sendCmd(kERR,"Unknown command");
}

// ------------------ E N D  C A L L B A C K  M E T H O D S ------------------

//-------------------- HELPER FUNCTION ---------------------------------------
int countSplitCharacters(String text, char splitChar) {
   int returnValue = 0;
   int index = -1;

   while (index > -1) {
     index = text.indexOf(splitChar, index + 1);

     if(index > -1) returnValue+=1;
   }

   return returnValue;
} 



// ------------------ S E T U P ----------------------------------------------

void attach_callbacks(messengerCallbackFunction* callbacks)
{
  int i = 0;
  int offset = kSEND_CMDS_END;
  while(callbacks[i])
  {
    cmdMessenger.attach(offset+i, callbacks[i]);
    i++;
  }
}

void setup() 
{
  // Listen on serial connection for messages from the pc
  // Serial.begin(57600);  // Arduino Duemilanove, FTDI Serial
  Serial.begin(9600); // Arduino Uno, Mega, with AT8u2 USB

  // cmdMessenger.discard_LF_CR(); // Useful if your terminal appends CR/LF, and you wish to remove them
  cmdMessenger.print_LF_CR();   // Make output more readable whilst debugging in Arduino Serial Monitor
  
  // Attach default / generic callback methods
  cmdMessenger.attach(kARDUINO_READY, arduino_ready);
  cmdMessenger.attach(unknownCmd);

  // Attach my application's user-defined callback methods
  attach_callbacks(messengerCallbacks);

  arduino_ready();

  // blink
  pinMode(13, OUTPUT);
}


// ------------------ M A I N ( ) --------------------------------------------

// Timeout handling
long timeoutInterval = 50; // 2 seconds
long previousMillis = 0;
int counter = 0;

void timeout()
{
  // blink
  if (counter % 2)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  counter ++;
}  

void loop() 
{
  // Process incoming serial data, if any
  cmdMessenger.feedinSerialData();

  // handle timeout function, if any
  if (  millis() - previousMillis > timeoutInterval )
  {
    timeout();
    char buf[64] = { '\0' };
    buf[0] = 'o';
    buf[1] = 'k';
    if(buf[0])
     cmdMessenger.sendCmd(kACK, buf);
    previousMillis = millis();
  }

  // Loop.
}
