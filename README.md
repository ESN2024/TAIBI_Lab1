# LED Chaser
#### Introduction:
Le but de ce lab est de concevoir et réaliser un LED Chaser en mettant en pratique les principes de la conception conjointe vus au cours. Les deux mécanismes (interruption et polling) ont été utilisés afin de répondre au cahier des charges.
**Interruption:** le bouton Trigger envoi une interruption afin de déclencher le LED Chaser.
**Polling:** la survéillance du registre DATA des 4 switchs par polling permet de controller la vitesse en utilisant 16 états.

#### L'architecture du système:
[Image de l'architecture]
Les blocs IP utilisés sont les suivants:
- **NIOS II Core:** un softcore d'architecture Harvard et de jeu d'instruction réduit (RISC 32 bits) en mode economy,
- **Memoire RAM 40,96 ko**.
- **JTAG UART:** permettant le débogage.
- **Clock**.
- **Trigger/IN:** entrée (bouton) qui permet d'effectuer *une lancée* de Chenillard avec interruption d'une priorité de IRQ1.
- **Switch_spped_4**: une entrée de 4 bits (boutons de switchs) pour fixer la vitesse.
- **LEDS_8**: sortie de 8 bits (LEDS).
