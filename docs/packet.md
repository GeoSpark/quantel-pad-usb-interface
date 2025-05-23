
## Quantel PAD input device packet format

### General description
- A packet is formed of 9 bytes.
- They are sent roughly every 10ms, implying a baud-rate of 9600.
- Packets are sent regardless of any input, so have to pay attention to key/pen/button flags.
- The MSb of byte 1 is always 1 to signify the start of a packet. All other bytes have the MSb cleared.
- Byte 9 is the XOR of each of the other bytes, masked to the least significant 7 bits.
- Pen position can be negative and uses 2's compliment, and seems to range from about -948, -528 in the top left, to 6759, 5324 in the bottom right.
- Key events are only sent on key transition, so key repeats have to be handled in software.
- It's probable that key data and pen data aren't transmitted in the same packet because of the use of byte 3, bit 6 for pen pressure. If so, this would probably be unnoticeable on original hardware because the screen refresh would only be 30 FPS.

### Packet structure

| Byte | Bits | Description                                                    |
|------|------|----------------------------------------------------------------|
| 1    | 7    | Start of packet - always set                                   |
|      | 6    | Keycode present in packet                                      |
|      | 5    | Pen data is present in packet                                  |
|      | 4    | Unknown                                                        |
|      | 3    | Joystick down                                                  |
|      | 2    | Joystick up                                                    |
|      | 1    | Joystick right                                                 |
|      | 0    | Joystick left                                                  |
| 2    | 7    | Always unset                                                   |
|      | 6    | Button 5, trigger                                              |
|      | 5    | Unknown - always set?                                          |
|      | 4    | Set if key up, unset if key down                               |
|      | 3    | Button 4                                                       |
|      | 2    | Button 3                                                       |
|      | 1    | Button 2                                                       |
|      | 0    | Button 1                                                       |
| 3    | 7    | Always unset                                                   |
|      | 6-0  | If byte 1 bit 6 is set, keycode                                |
|      | 6    | If byte 1 bit 6 is unset, most significant bit of pen pressure |
|      | 5-0  | If byte 1 bit 6 is unset, unknown                              |
| 4    | 7    | Always unset                                                   |
|      | 6-0  | Most significant bits of pen x position                        |
| 5    | 7    | Always unset                                                   |
|      | 6-0  | Least significant bits of pen x position                       |
| 6    | 7    | Always unset                                                   |
|      | 6-0  | Most significant bits of pen y position                        |
| 7    | 7    | Always unset                                                   |
|      | 6-0  | Least significant bits of pen y position                       |
| 8    | 7    | Always unset                                                   |
|      | 6-0  | Least significant bits of pen pressure                         |
| 9    | 7    | Always unset                                                   |
|      | 6-0  | XOR of previous 8 bytes                                        |
