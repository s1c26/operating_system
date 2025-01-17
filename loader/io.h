#ifndef _IO_H
#define _IO_H

#include "stdint.h"

/**
 * Outputs a byte to an I/O port
 * 
 * @param val byte value to output
 * @param port port to output to
 */
extern void outb(uint8_t val, uint16_t port);

/**
 * Outputs a word (16-bit) value to an I/O port
 * 
 * @param val word value to output
 * @param port port to output to
 */
extern void outw(uint16_t val, uint16_t port);

/**
 * Outputs a long (32-bit) value to an I/O port
 * 
 * @param val long value to output
 * @param port port to output to
 */
extern void outl(uint32_t val, uint16_t port);

/**
 * Reads a byte from an I/O port
 * 
 * @param port port to read from
 * @return byte value from port
 */
extern uint8_t inb(uint16_t port);

/**
 * Reads a word (16-bit) value from an I/O port
 * 
 * @param port port to read from
 * @return word value from port
 */
extern uint16_t inw(uint16_t port);

/**
 * Reads a long (32-bit) value from an I/O port
 * 
 * @param port port to read from
 * @return long value from port
 */
extern uint32_t inl(uint16_t port);

#endif
