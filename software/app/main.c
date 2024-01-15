#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "unistd.h" //access to usleep



volatile int edge_capture;


static void handle_interrupts(void* context)
{   
    volatile int* edge_capture_ptr = (volatile int*) context;
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE,0);

	volatile  unsigned char one = 0x01;
	for(int i = 0;i <= 7; i++){

				IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,one);
				usleep(10000);
				one = one << 1;

			}
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,0x00);


}


static void init_interrupt_pio()
{
    //Recast the edge_capture point to match the
    //alt_irq_register() function prototypo
    void* edge_capture_ptr = (void*)&edge_capture;

    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(TRIGGER_BASE,0x1);
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(TRIGGER_BASE,0);
    alt_ic_isr_register(TRIGGER_IRQ_INTERRUPT_CONTROLLER_ID,
        TRIGGER_IRQ, handle_interrupts, edge_capture_ptr, 0x0);

	//mettre les leds à zeros
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_8_BASE,0x00);

}



int main(){

    // Initialize the interrupt
    init_interrupt_pio();
	while(1){
		if (edge_capture == 0x1) //bit position 0 corresponds to button press
			{
				edge_capture = 0; // reset variable to "unregister" event
			}
	}

        

    
}