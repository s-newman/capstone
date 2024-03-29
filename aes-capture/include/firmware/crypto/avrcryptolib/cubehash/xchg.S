/* xchg.S */
/*
    This file is part of the AVR-Crypto-Lib.
    Copyright (C) 2006-2010 Daniel Otte (daniel.otte@rub.de)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

.global xchg32_array
xchg32_array:
   movw r26, r24
   movw r30, r22
1:
   ld r24, X
   ld r25, Z
   st X+, r25
   st Z+, r24
   ld r24, X
   ld r25, Z
   st X+, r25
   st Z+, r24
   ld r24, X
   ld r25, Z
   st X+, r25
   st Z+, r24
   ld r24, X
   ld r25, Z
   st X+, r25
   st Z+, r24
   dec r20
   brne 1b
   ret

