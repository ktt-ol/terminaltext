const byte PSPAD_REQUEST_CMD = 0x42;
const byte PSPAD_IDLE = 0x00;

#define PSPAD_MASK_SELECT 0x01
#define PSPAD_MASK_SELECT 0x02
#define PSPAD_MASK_SELECT 0x04
#define PSPAD_MASK_START  0x08
#define PSPAD_MASK_UP     0x10
#define PSPAD_MASK_RIGHT  0x20
#define PSPAD_MASK_DOWN   0x40
#define PSPAD_MASK_LEFT   0x80

#define PSPAD_MASK_L2 0x01
#define PSPAD_MASK_R2 0x02
#define PSPAD_MASK_L1 0x04
#define PSPAD_MASK_R1 0x08
#define PSPAD_MASK_TRIANGLE 0x10
#define PSPAD_MASK_CIRCLE   0x20
#define PSPAD_MASK_CROSS    0x40
#define PSPAD_MASK_SQUARE   0x80

#define PSPAD_MULTITAP_PAD1   0x01
#define PSPAD_MULTITAP_PAD2   0x02
#define PSPAD_MULTITAP_PAD3   0x03
#define PSPAD_MULTITAP_PAD4   0x04


class PSPad {
private:
	byte pinClock;
	byte pinCmd;
	byte pinData;
	byte pinAtt;
	byte multitapPort;
	int bitDelay;
	bool isAnalog;
	
	byte buf[6];
public:

	PSPad(byte pinCmd, byte pinData, byte pinClock, byte pinAtt, byte multitapPort = PSPAD_MULTITAP_PAD1)
		: pinCmd(pinCmd), pinData(pinData),
		  pinClock(pinClock), pinAtt(pinAtt),
		  multitapPort(multitapPort),
		  bitDelay(10)
	{
		pinMode(pinCmd, OUTPUT);

		pinMode(pinData, INPUT);
		digitalWrite(pinData, HIGH);

		pinMode(pinClock, OUTPUT);
		digitalWrite(pinClock, HIGH);

		pinMode(pinAtt, OUTPUT);
		digitalWrite(pinAtt, HIGH);
	}

	inline void update() {
		read();
	}
private:
	byte transferByte(byte out = PSPAD_IDLE) {
		byte in = 0;

		for (int i=0; i < 8; i++) {
			digitalWrite(pinClock, LOW);

			if (out & (1 << i)) {
				digitalWrite(pinCmd, HIGH);
			} else {
				digitalWrite(pinCmd, LOW);
			}

			delayMicroseconds(bitDelay);
			if (digitalRead(pinData) == HIGH) {
				in |= B1 << i;
			}

			digitalWrite(pinClock, HIGH);
			delayMicroseconds(bitDelay);
		}

		return in;
	}

	void read() {
		digitalWrite(pinAtt, LOW);

		transferByte(multitapPort);
		byte padId = transferByte(PSPAD_REQUEST_CMD);

		if (padId == 0x80) { // multitap
			transferByte(); // 0x5a
			padId = transferByte();
		}

		if (padId == 0x73) {
			isAnalog = true;
		} else {
			isAnalog = false;
		}

		transferByte(); // 0x5a


		buf[0] = ~transferByte();
		buf[1] = ~transferByte();

		if (isAnalog) {
			buf[2] = transferByte();
			buf[3] = transferByte();
			buf[4] = transferByte();
			buf[5] = transferByte();
		}

		digitalWrite(pinAtt, HIGH);
	}
public:

	inline bool pressedUp() { return buf[0] & PSPAD_MASK_UP; }
	inline bool pressedRight() { return buf[0] & PSPAD_MASK_RIGHT; }
	inline bool pressedDown() { return buf[0] & PSPAD_MASK_DOWN; }
	inline bool pressedLeft() { return buf[0] & PSPAD_MASK_LEFT; }

	inline bool pressedSelect() { return buf[0] & PSPAD_MASK_SELECT; }
	inline bool pressedStart() { return buf[0] & PSPAD_MASK_START; }

	inline bool pressedR1() { return buf[1] & PSPAD_MASK_R1; }
	inline bool pressedR2() { return buf[1] & PSPAD_MASK_R2; }
	inline bool pressedL1() { return buf[1] & PSPAD_MASK_L1; }
	inline bool pressedL2() { return buf[1] & PSPAD_MASK_L2; }

	inline bool pressedTriangle() { return buf[1] & PSPAD_MASK_TRIANGLE; }
	inline bool pressedCircle() { return buf[1] & PSPAD_MASK_CIRCLE; }
	inline bool pressedCross() { return buf[1] & PSPAD_MASK_CROSS; }
	inline bool pressedSquare() { return buf[1] & PSPAD_MASK_SQUARE; }

	inline char rightStickLeftRight() { return buf[2] - 128;}
	inline char rightStickUpDown() { return buf[3] - 128;}
	inline char leftStickLeftRight() { return buf[4] - 128;}
	inline char leftStickUpDown() { return buf[5] - 128;}

};
