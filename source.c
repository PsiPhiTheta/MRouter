/* Mini Assignment 2015-16. Friday groups */

//0. INFORMATION
	//Author: Thomas Hollis
	//Last modified: 28 March 2016
	//Sections editable by examiner: 2, 4.1, 4.2, 4.3

//1. INCLUSIONS
	#include <stdio.h> //only library required for this program
	//#include <stdlib.h>
	//#include <string.h>
	//#include <math.h>
	//#include <complex.h>
	//#include <ctype.h>
	//#include <gsl/gsl_linalg.h>
	//#include <stdbool.h>

//2. DEFINITIONS	
	#define NPORT 7 //number of authorised ports
	#define NLINK 4 //number of dotten decimal parts to link ID
	#define NPKTS 5 //number of packets
	#define NPKTSL 5 //length of packets
	//#define PI 3.1415926
	//#define E 2.71828182846
	//#define E0 0.00000000000885
	

//3. FUNCTION PROTOTYPES
	int is_authorised(int port, int authPorts[]); //determines if a packet is authorised
	int packet_route(int pkt_ID [], int local_ID []); //determines packet route
	void display_packet(int authorised, int routed); //determines if a packet is forwarded or discarded
	
//4. MAIN 
	int main(void) {

	//4.1 Sample list of test packets:
		int Pkts[NPKTS][NPKTSL]={
			{192,168,10,2,212	},
			{192,168,2,100,120	},
			{10,190,200,10,80	},
			{192,168,10,200,173	},
			{10,100,1,40,25		}
		};

	//4.2 ID of incoming link: 
		int incoming_link_ID[NLINK] = {192,168,10,0}; //note: four part dotted decimal
		
	//4.3 Authorised ports: 
		int authPorts[NPORT] = {20,73,60,80,212,434,2211}; //note: max 2^16 - 1 = 65,535
		
	//4.4 Print incoming link & authorised ports
		printf("\n Incoming link ID: ");
		for (int i = 0 ; i<(NLINK-1) ; i++) {
			printf("%d.", incoming_link_ID[i]);
		} 
		printf("%d", incoming_link_ID[NLINK-1]); //used to omit final "."
		printf("\n");
		
		printf("\n Authorised ports: ");
		for (int i = 0 ; i<(NPORT-1) ; i++) {
			printf("%d,", authPorts[i]);
		} 
		printf("%d", authPorts[NPORT-1]); //used to omit final ","
		printf("\n");

	//4.5 Packet processing & printing
		for (int i = 0 ; i<NPKTS ; i++) { //executes code bellow for all packets
			int port = Pkts[i][NPKTSL-1]; //extracts port number from packets
			int authorised = is_authorised(port, authPorts); //calls function to check if port is authorised
			int routed = packet_route(Pkts[i], incoming_link_ID); //calls function to check if packet is routed
	
			printf("\n "); 
			for (int j = 0 ; j<(NPKTSL-2) ; j++) { //prints packet ID
			printf("%d.", Pkts[i][j]);
			} 
			printf("%d:", Pkts[i][NPKTSL-2]); //used to replace "." by ":"
			printf("%d \t", Pkts[i][NPKTSL-1]); //used to omit final "."
		
			display_packet (authorised, routed); //prints packet authorisation and routing status
		}
		
		printf("\n");
		
	return 0;
	}

//5. FUNCTIONS 
	int is_authorised(int port, int authPorts[]) { 
		for (int i = 0 ; i<NPORT ; i++) { //runs through all authorised ports
			if (port == authPorts[i]) { //checks if port matches authorised ports
				return 1; //returns 1 if port number matches authPort
			}
		}
	return 0; //otherwise returns 0
	}
	
	int packet_route(int pkt_ID[], int local_ID[]) { 
		for (int i=0 ; i < 3 ; i++) { //runs through the first 3 parts of pkt_ID
			if (pkt_ID[i] != local_ID[i]) { //checks if pckt_ID matches local_ID
			return 1; // returns 1 if the first three parts of the ID's don't match
			}
		}	
		return 0; //otherwise returns 0 
	} 

	void display_packet(int authorised, int routed) { // displays whether the packet is forwarded or discarded
		if (authorised == 1) { //if authorised prints authorised
			printf(" \t Authorised     ");
			if (routed == 1) { //prints routing status
				printf(" \t Packet Routed");
			}
			else {
				printf(" \t Packet Discarded");
			}
		}
		else {
			printf(" \t Not Authorised \t Packet Discarded"); //if not authorised prints not authorised and packet discarded
		}
	} 
	
//6. DEBUG STATUS 
	//debugged
