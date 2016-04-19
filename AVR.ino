#define I2C_SLAVE_ADDRESS 0x1 // Address of the slave

#include <TinyWireS.h>
#include <math.h>

int a=0;
int b=0;
int d=0;


void requestEvent()
{ 
  TinyWireS.send((int)sqrt(pow(a,2)+pow(b,2)));
}

void receiveEvent(uint8_t howMany)
{   
  if (howMany < 1)
    {
        return;
    }
  if(d==0){
    a = TinyWireS.receive(); 
    d=1;
  }else{
    b = TinyWireS.receive(); 
    d=0;
  } 
}

void setup() {

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);  
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);  
  }

void loop() {
 TinyWireS_stop_check();
}

