
#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "unistd.h" //access to usleep


volatile unsigned char edge_cap;
volatile unsigned char speed;

// La fonction Interrupt Sub-Routine (ISR)
static void handle_interrupts(void* context)
{   
	// Pointeur vers la variable edge_cap
    volatile unsigned char* edge_cap_ptr = (volatile unsigned char*) context;
	// Lire le registre edgec_apture et enregister le contenu dans la variable edge_cap   
    *edge_cap_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE);
    // Mettre le bit numéro 0 à l'état 1 pour le reset du registre edge_capture (pas besoin d'utiliser un masque car on a un seul bit)
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE,0);
	// Variable pour allumer les LEDs
	volatile  unsigned char one = 0x01;
	// Boucle pour allumer les LEDs
	for(unsigned char i = 0;i <= 7; i++){
				// Ecrire dans le registre DATA de la base LEDS_8_BASE le contenu de la variable one
				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,one);
				// Mettre en sleep, speed est géré par polling dans la fonction main
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
    void* edge_cap_ptr = (void*)&edge_cap;
	//Activer la bonne interruption : mettre '1' dans le bit correspondant l'interruption d u trigger 
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(TRIGGER_BASE,0x1);
	// Rénitialisation du registre edge_capture
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE,0);
	// Enregistrer l'interruption "handle_interrupts"
    alt_irq_register( TRIGGER_IRQ, edge_cap_ptr, (void*)handle_interrupts); 
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