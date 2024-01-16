#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "unistd.h" //access to usleep



volatile int edge_capture;
volatile int speed;

// La fonction Interrupt Sub-Routine
static void handle_interrupts(void* context)
{   
	// Pointeur vers la variable edge_capture
    volatile int* edge_capture_ptr = (volatile int*) context;
	// Lire le registre edgecapture et enregister le contenu dans la variable edge_capture   
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE);
    // Mettre le bit numéro 0 à l'état 1 pour le reset (pas besoin d'utiliser un masque car on a un seul bit)
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE,0);
	// Variable pour allumer les LEDs
	volatile  unsigned char one = 0x01;
	// Boucle pour allumer les LEDs
	for(int i = 0;i <= 7; i++){
				// Ecrire dans le registre DATA de la base LEDS_8_BASE le contenu de la variable one
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,one);
				// Mettre en sleep, speed est gérer par polling dans la fonction main
				usleep(10000 * speed);
				// Décalage à gauche
				one = one << 1;
			}
	// Après l'allumage de tout les LEDs on les mets à zeros
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,0x00);


}

// Initialisation des interruptions
static void init_interrupt_pio()
{
	// Casting
    void* edge_capture_ptr = (void*)&edge_capture;
	// Reset (comme vue au dessus)
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE,0);
	// Enregistrer l'interruption "handle_interrupts"
    alt_irq_register( TRIGGER_IRQ, edge_capture_ptr, (void*)handle_interrupts); 
	// Mettre les leds à zeros
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,0x00);

}







int main(){

    // Inittalisation de l'interruption
    init_interrupt_pio();

	// l'utilisation du polling pour changer la vitesse, il y 16 états
	while(1){
		speed = IORD_ALTERA_AVALON_PIO_DATA(SWITCH_SPEED_4_BASE);		
	}
}