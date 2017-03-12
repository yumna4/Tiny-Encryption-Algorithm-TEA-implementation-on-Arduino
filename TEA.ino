#include <SoftwareSerial.h>
 unsigned int p [2] = {0xAABBCCDD, 0xAABBCCDE};

unsigned int k [4] = {0,2,3,4};

unsigned int c [2] = {0xE4A029D3, 0x517420C2};
void setup() {
 
  // put your setup code here, to run once:
Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
char ascii[32];
Serial.println("Hi there");
sprintf(ascii, "original: 0x%08X 0x%08X \n",(int)p[0],(int)p[1]);
Serial.println(ascii);
delay(10000);
encrypt(p,k);
sprintf(ascii,"encrypted:0x%08X 0x%08X \n",(int)p[0],(int)p[1]); 
Serial.println(ascii);
delay(10000);
decrypt(p,k);
sprintf(ascii,"decrypted:0x%08X 0x%08X \n",(int)p[0],(int)p[1]);
Serial.println(ascii);
delay(10000);
}





void encrypt (unsigned int* v, unsigned int* k) {
    unsigned int v0=v[0], v1=v[1],sum=0,i;
    unsigned int delta=0x9e3779b9; 
    unsigned int k0=k[0], k1=k[1], k2=k[2], k3=k[3]; 
    for (i=0; i < 32; i++) { 
      sum += delta;
      v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
      v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
      } 
      v[0]=v0; v[1]=v1;
      }

void decrypt (unsigned int* v, unsigned int* k) {
  unsigned int v0=v[0], v1=v[1], sum=0xC6EF3720, i; 
  unsigned int delta=0x9e3779b9;
  unsigned int k0=k[0], k1=k[1], k2=k[2], k3=k[3]; 
  for (i=0; i<32; i++) { 
    v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    sum -= delta;
  }
  v[0]=v0; v[1]=v1;
}




