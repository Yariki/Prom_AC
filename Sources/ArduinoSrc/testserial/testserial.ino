
#define MAX_DATA_SIZE 64

byte buffer[MAX_DATA_SIZE];
boolean isReady = false;
int countBytes = 0;

void setup(){
  Serial.begin(9600);
  initBuffer();
}


void loop(){
  if(Serial.available() > 0 ){
      int av = Serial.available();
      for(int i = 0; i < av;i++){
        buffer[countBytes] = Serial.read();
        countBytes++;
      }
  }
  if(countBytes >= MAX_DATA_SIZE){
    byte incoming = buffer[0];
    switch(incoming){
      case 0:
        Serial.println("true");
        break;
      case 1:
        Serial.println("false");
        break;
    }
    Serial.flush();
    countBytes = 0;
    initBuffer();
  }
  
}

void initBuffer(){
  for(int i = 0; i < MAX_DATA_SIZE;i++)
    buffer[i] = ' ';
//  buffer[0] = 'A';
//  buffer[MAX_DATA_SIZE - 1] = 'Z';
}


