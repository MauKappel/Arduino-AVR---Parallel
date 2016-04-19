#include <Wire.h>
int q=44;
int end_array[42]={0};
int s=0;
long startTime1;
long endTime;
long startTime;
long endTime1;
void setup() {
  startTime1=millis();
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)

  pinMode(41, INPUT);
  pinMode(42, INPUT);
  pinMode(43, INPUT);
}



void loop() {

    int start[42][3];
    int devices = 0;            //Anzahl von verfuegbaren Controllern
    int n = 0;
    int a = 0;
    char num_buffer[10];
    while (digitalRead(41) == LOW)
    {
      n++;
      if(n==2421){
        n=0;
      }
    }
  
    srand(n+1);
    for(int u=0;u<=30;u++){             //x aufzaehlen
      for(int i=1;i<=2;i++){            //y aufzaehlen
      start[u][i]= rand() % 127 + 6;    //Zufallszahl fuer start[x][y]
      if(start[u][i]==44){
        start[u][i]=45;
      }
      }  
    }
    start[0][1]=43;
    start[0][2]=41;
    if(digitalRead(41)==HIGH){
      devices++;
    }    
    if(digitalRead(42)==HIGH){
      devices++;
    }
    if(digitalRead(43)==HIGH){
      devices++;
    }
    
    endTime1 = millis(); 
    send(start, devices);         //Sende Startwerte zu Geraete
    Serial.print("Seq: ");Serial.println(endTime1-startTime1);//sequentiell
    Serial.print("Parallel: ");Serial.println(endTime-startTime);//parallel
    Serial.print("Alles: ");Serial.println(endTime-startTime1);//alles
    while(1==1){}
   }

void send(int start[41][3], int devices){ 
  startTime = millis();  
  int a=1;
  int c=0;
  int k=0;
      for(int u=0; u<=30; u++){

               for(int a=1; a<=devices; a++){      
               delay(5);
               Wire.beginTransmission(a);
               Wire.write(start[u][1]);           
               Wire.endTransmission();  
               Serial.println(start[u][1]);   
               Wire.beginTransmission(a); 
               Wire.write(start[u][2]);   
               Wire.endTransmission();  
               Serial.println(start[u][2]);
               if(u==30){
                goto end;
               }
               u++;
               }
               u--; 
               delay(5);
               end: for(int a=1; a<=devices; a++){
               Serial.print("Receive start:"); 
               Wire.requestFrom(a, 1);    
               c = Wire.read(); // receive a byte as character
               Serial.print(a);Serial.print(": ");Serial.println(c);
               end_array[s]=c;  
               }
      }
    endTime = millis();         
}


