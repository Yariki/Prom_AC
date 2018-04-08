// CmdMessenger library available from https://github.com/dreamcat4/cmdmessenger
#include <CmdMessenger.h>
#include <HashMap.h>
// Base64 library available from https://github.com/adamvr/arduino-base64
#include <Base64.h>

// Streaming4 library available from http://arduiniana.org/libraries/streaming/
#include <Streaming.h>

#include "IndicatorProcessObject.h"
#include "SignalProcessInfo.h"
#include "ObjectProcessInfo.h"


struct ObjectInfo {
	byte IsWorking;
	int PinIndex;
};

const int MapCount = 3;
// Mustnt conflict / collide with our message payload data. Fine if we use base64 library ^^ above
char field_separator = ',';
char command_separator = ';';
char params_separator = '|';
char alert_start_char = '(';
char alert_finish_char = ')';
char alert_split_signals_char = '/';
char alert_split_signals_value_char = ':';

//storage 
HashType<int,ObjectProcessInfo*> hashRawArray[MapCount]; 
//handles the storage [search,retrieve,insert]
HashMap<int,ObjectProcessInfo*> hashMap = HashMap<int,ObjectProcessInfo*>( hashRawArray , MapCount ); 

int  StartedCmd = 7;
int  StopedCmd = 8;
int  AlertCmd = 9;
const int IDLenght = 5;


// Attach a new CmdMessenger object to the default Serial port
CmdMessenger cmdMessenger = CmdMessenger(Serial, field_separator, command_separator);




// ------------------ C M D  L I S T I N G ( T X / R X ) ---------------------



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
  Start, // 004 in this example
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
  String inputData = getAllDataFromSerialPort();
  if(!inputData.length())
  {
    cmdMessenger.sendCmd(kERR,"Start command is  empty");
    return;
  }
 /* char str[320];
  inputData.toCharArray(str,320);
  cmdMessenger.sendCmd(kACK,str);*/
  
  int count = countSplitCharacters(inputData, params_separator);
  count++;
 /* char chCount [16];
  String strCount = String(count);
  strCount.toCharArray(chCount,16);
  cmdMessenger.sendCmd(kACK,chCount);*/
  int arr[count];
  findAllObjectsId(arr,count,&inputData);
  for(int i = 0 ; i < count; i++){
    StartObject(arr[i]);
    Started(arr[i]);
  }
  
}

void Stop()
{
  // To avoid conflicts with the control characters and any newline characters
  // Message length increases about 30%-40%
  String inputData = getAllDataFromSerialPort();
  if(!inputData.length())
  {
    cmdMessenger.sendCmd(kERR,"Start command is  empty");
    return;
  }
  /*char str[320];
  inputData.toCharArray(str,320);
  cmdMessenger.sendCmd(kACK,str);*/
  
  int count = countSplitCharacters(inputData, params_separator);
  count++;
  /*char chCount [16];
  String strCount = String(count);
  strCount.toCharArray(chCount,16);
  cmdMessenger.sendCmd(kACK,chCount);*/
  
  int arr[count];
  findAllObjectsId(arr,count,&inputData);
  for(int i = 0 ; i < count; i++){
    StopObject(arr[i]);
    Stoped(arr[i]);
  }

}

void EmergencyStop()
{
	for(int i = 0; i < MapCount;i++){
		ObjectProcessInfo* info = (ObjectProcessInfo*)hashRawArray[i].getValue();
		if(info->isWorking()){
			info->setWorking(false);
			Stoped(hashRawArray[i].getHash());
		}
	}
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
   int lenght = text.length();
   for(int i = 0; i < lenght;i++){
	if(text[i] == splitChar)
	returnValue++;
   }
   return returnValue;
} 

void Started(int id){
  char chId [IDLenght];
  String strId = String(id);
  strId.toCharArray(chId,IDLenght);
  cmdMessenger.sendCmd(StartedCmd,chId);
}

void Stoped(int id){
  char chId [IDLenght];
  String strId = String(id);
  strId.toCharArray(chId,IDLenght);
  cmdMessenger.sendCmd(StopedCmd,chId);
}

void Alert(){
	//char* alertMsg = "1(2:3/3:5/4:6)|3(2:1/3:1/4:1)";

	String message = "";
	for(int i = 0; i < MapCount;i++){
		ObjectProcessInfo* info = (ObjectProcessInfo*)hashRawArray[i].getValue();
		if(info->isWorking()){
			String temp = info->checkSignals();
			if(temp.length() > 0){
				message +=  "|" + temp;
			}
		}
	}
	if(message.length() > 0){
		cmdMessenger.sendCmd(AlertCmd, (char*)message.c_str());
	}


}

void StartObject(int id){

	ObjectProcessInfo* info = hashMap.getValueOf(id);
	if(info){
		info->setWorking(true);
		delay(1000);
	}
}

void StopObject(int id){

	ObjectProcessInfo* info = hashMap.getValueOf(id);
	if(info){
		info->setWorking(false);
		delay(1000);
	}

}

String getAllDataFromSerialPort(){
	String inputData;
	while ( cmdMessenger.available() )
	{
	char buf[350] = { '\0' };
	cmdMessenger.copyString(buf, 350);
	inputData = inputData + String(buf);
	}
	return inputData;
}

void findAllObjectsId(int* massiv, int count, String* input){
	int lastIndex = 0;
	int currentIndex = 0;

	if(count == 1){
		char charId[16];
		if(input->length() == 0 || input->length() >= 16){
			  return;
		}
		input->toCharArray(charId,16);
		int id = atoi(charId);
		massiv[0] = id;
		return;
	}

	for(int i = 0; i < count; i++){
		currentIndex = input->indexOf(params_separator,lastIndex);
		if(currentIndex == -1){
			  if(lastIndex > 0){
				char charId[16];
  				  String strId = input->substring(lastIndex);
  					if(strId.length() == 0 || strId.length() >= 16){
  					  break;
    				}
    				strId.toCharArray(charId,16);
    				int id = atoi(charId);
    				massiv[i] = id;  
			  }        
			  break;
		}
		char charId[16];
		String strId = input->substring(lastIndex,currentIndex);
		if(strId.length() == 0 || strId.length() >= 16){
			  break;
		}
		strId.toCharArray(charId,16);
		int id = atoi(charId);
		massiv[i] = id;
		lastIndex = currentIndex + 1;
	}
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

void setupObjectsMap(){
	
	ObjectProcessInfo* oi = new ObjectProcessInfo();
	oi->setInfo(1001,0,7);
	SignalProcessInfo* si = new SignalProcessInfo();
	si->setInfo(99,8);
	oi->addSignal(si);
	hashMap[0](1001,oi);

	oi = new ObjectProcessInfo();
	oi->setInfo(1002,0,11);
	si = new SignalProcessInfo();
	si->setInfo(102,21);
	oi->addSignal(si);
	hashMap[1](1002,oi);

	oi = new ObjectProcessInfo();
	oi->setInfo(1003,0,12);
	si = new SignalProcessInfo();
	si->setInfo(10,13);
	oi->addSignal(si);
	hashMap[2](1003,oi);
	
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
  setupObjectsMap();
}


// ------------------ M A I N ( ) --------------------------------------------

// Timeout handling
long timeoutInterval = 100; // 2 seconds
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
    previousMillis = millis();
	Alert();
  }
  // Loop.
}
