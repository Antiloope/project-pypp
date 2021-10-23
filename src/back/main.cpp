#include "main.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "player/player.h"

#define PERMS 0644
struct my_msgbuf {
   long mtype;
   int mtext[16];
};

struct my_msgbuf buf;
int msqid;

using namespace std;
using namespace pypp;
//
// // Pass-through function.
// int inout( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
//            double streamTime, RtAudioStreamStatus status, void *data )
// {
//   // Since the number of input and output channels is equal, we can do
//   // a simple buffer copy operation here.
//   if ( status ) std::cout << "Stream over/underflow detected." << std::endl;
// //  cout << nBufferFrames << endl;
//   //memcpy( outputBuffer, inputBuffer, nBufferFrames * 16);
//    int32_t* ob = (int32_t*) outputBuffer;
//    int32_t* ib = (int32_t*) inputBuffer;
//   for(int i = 0; i < nBufferFrames/32; i++){
//       buf.mtext[i] = ib[i];
//   }
//   int l=1;
//   int r=1;
//   int i =0;
//   while( i < nBufferFrames  ) {
//      ob[i] = (int32_t) ( ib[i+1] * l + .5 );
//      ++i;
//      ob[i] = (int32_t) ( ib[i] * r + .5 );
//      ++i;
//   }
//   msgsnd(msqid, &buf, 16, IPC_NOWAIT);
//   return 0;
// }

int main(int argv,char* argc[]) {
   //string command = "python /usr/local/src/front/main.py &";
    string command = "python /home/antiloope/Documents/projects/project-pypp/src/front/main.py &";
    system(command.c_str());

    int len;
   key_t key;
   system("touch msgq.txt");
   key = 1234;

   if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
   }
   printf("message queue: ready to send messages.\n");
   printf("Enter lines of text, ^D to quit:\n");
   buf.mtype = 1; /* we don't really care in this case */

   Player* player = Player::getInstance();

   player->init();
  //
  //    RtAudio adac;
  //    cout << adac.getDeviceCount() << endl;
  // if ( adac.getDeviceCount() < 1 ) {
  //   std::cout << "\nNo audio devices found!\n";
  //   exit( 0 );
  // }
  // // Set the same number of channels for both input and output.
  // unsigned int bufferBytes, bufferFrames = 512;
  // RtAudio::StreamParameters iParams, oParams;
  // iParams.deviceId = 0; // first available device
  // iParams.nChannels = 2;
  // oParams.deviceId = 0; // first available device
  // oParams.nChannels = 2;
  // RtAudio::StreamOptions options;
  // options.flags = RTAUDIO_HOG_DEVICE | RTAUDIO_NONINTERLEAVED | RTAUDIO_MINIMIZE_LATENCY;
  // try {
  //   adac.openStream( &oParams, &iParams, RTAUDIO_SINT32, 48000, &bufferFrames, &inout, (void *)&bufferBytes, &options);
  // }
  // catch ( RtAudioError& e ) {
  //   e.printMessage();
  //   exit( 0 );
  // }
  // bufferBytes = bufferFrames;
  // try {
  //   adac.startStream();
  //   std::cout << "\nRunning ... press <enter> to quit.\n";
  // }
  // catch ( RtAudioError& e ) {
  //   e.printMessage();
  //
  // }

   char a;
   cin >> a;

   if (msgctl(msqid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");

  //  adac.stopStream();
   return 0;

}
