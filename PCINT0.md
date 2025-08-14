This document covers the configuration and usage of Pin Change Interrupt 0 (PCINT0) on the ATmega328 microcontroller. It explains how to enable interrupts for pins PB0–PB7 using PCICR and PCMSK0, how to clear the PCIF0 flag, write the ISR, and implement logic to detect pin changes.

---

## **PCINT0 Overview**

| Group     | Pins     | Port     | Interrupt Vector |
|-----------|----------|----------|------------------|
| PCINT0    | PB0–PB7  | PORTB    | `PCINT0_vect`    |

Pin Change Interrupt 0 monitors all pins on PORTB. Any logical change (rising or falling edge) on an enabled pin will trigger the interrupt.

---

## **PCICR – Pin Change Interrupt Control Register**

| Bit | Name   | Description                          |
|-----|--------|--------------------------------------|
| 0   | PCIE0  | Enable Pin Change Interrupt for PCINT0 group |

### **Enable PCINT0 Group:**

```c
bitSet(PCICR, PCIE0); // Enable pin change interrupt for PORTB (PCINT0 group)
```

---

## **PCMSK0 – Pin Change Mask Register 0**

| Bit  | Name     | Pin   | Description                                 |
|------|----------|--------|---------------------------------------------|
| 0    | PCINT0   | PB0   | Enable pin change interrupt for PB0         |
| 1    | PCINT1   | PB1   | Enable pin change interrupt for PB1         |
| 2    | PCINT2   | PB2   | Enable pin change interrupt for PB2         |
| 3    | PCINT3   | PB3   | Enable pin change interrupt for PB3         |
| 4    | PCINT4   | PB4   | Enable pin change interrupt for PB4         |
| 5    | PCINT5   | PB5   | Enable pin change interrupt for PB5         |
| 6    | PCINT6   | PB6   | Enable pin change interrupt for PB6         |
| 7    | PCINT7   | PB7   | Enable pin change interrupt for PB7         |

---

### **Enable Interrupts for Individual Pins (Examples)**

```c
bitSet(PCMSK0, PCINT0); // Enable interrupt for PB0
bitSet(PCMSK0, PCINT1); // Enable interrupt for PB1
bitSet(PCMSK0, PCINT2); // Enable interrupt for PB2
bitSet(PCMSK0, PCINT3); // Enable interrupt for PB3
bitSet(PCMSK0, PCINT4); // Enable interrupt for PB4
bitSet(PCMSK0, PCINT5); // Enable interrupt for PB5
bitSet(PCMSK0, PCINT6); // Enable interrupt for PB6
bitSet(PCMSK0, PCINT7); // Enable interrupt for PB7
```
You can enable multiple pins simultaneously by setting multiple bits.

```c
PCMSK0 |= (1 << PCINT1) | (1 << PCINT3) | (1 << PCINT5); // Enable PB1, PB3, PB5
```

---

## **PCIFR – Pin Change Interrupt Flag Register**

| Bit | Name   | Description                          |
|-----|--------|--------------------------------------|
| 0   | PCIF0  | Pin Change Interrupt Flag for PCINT0 |

### **Clear PCINT0 Flag Manually:**

```c
intFlag_clear(PCIFR, PCIF0); // Clear PCINT0 interrupt flag
```

> [!NOTE]
> The flag is automatically cleared when the ISR is executed.

---

## **Writing the ISR for PCINT0**

The ISR is triggered on any logical change of enabled pins in PORTB. You must read the current pin state and compare it to the previous state to detect rising or falling edges.

### **Example ISR:**
```c
ISR(PCINT0_vect)
{
    if (bitCheckHigh(PINB, 2)) 
    {
        // Rising edge on PB2
    } 
    else 
    {
        // Falling edge on PB2
    }
}
```

---

## **Complete Initialization Example**

```c
void pcint0_Init(void) 
{
    GPIO_Config_INPUT(DDRB, PB2);     // Configure PB2 as input
    bitSet(PCICR, PCIE0);             // Enable PCINT0 group
    bitSet(PCMSK0, PCINT2);           // Enable interrupt for PB2
    globalInt_Enable;                 // Enable global interrupts
}
```

---

## **Summary of PCINT0 Setup**

| Step                        | Register | Action                                  |
|-----------------------------|----------|-----------------------------------------|
| Configure PBx as input      | DDRB     | `GPIO_Config_INPUT(DDRB, PBx)`          |
| Enable PCINTx in mask       | PCMSK0   | Set `PCINTx` bit                        |
| Enable PCINT0 group         | PCICR    | Set `PCIE0` bit                         |
| Enable global interrupts    | SREG     | Set `SREG_I` bit                        |
| Write ISR                   | PCINT0_vect | Detect and handle pin changes         |

> [!CAUTION]
> Pin change interrupts are level-agnostic. You must track previous pin states to determine edge direction.

# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
