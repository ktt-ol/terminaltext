//  _  __               _   _       _ _  _   _ _     _        _  __  __ _     _____         _           _ _                         ____       _        ____                       
// | |/ /_ __ ___  __ _| |_(_)_   _(_) |(_)_(_) |_  | |_ _ __(_)/ _|/ _| |_  |_   _|__  ___| |__  _ __ (_) | __                    | __ )  ___| |_ __ _/ ___| _ __   __ _  ___ ___ 
// | ' /| '__/ _ \/ _` | __| \ \ / / | __/ _` | __| | __| '__| | |_| |_| __|   | |/ _ \/ __| '_ \| '_ \| | |/ /                    |  _ \ / _ \ __/ _` \___ \| '_ \ / _` |/ __/ _ \
// | . \| | |  __/ (_| | |_| |\ V /| | || (_| | |_  | |_| |  | |  _|  _| |_    | |  __/ (__| | | | | | | |   <                     | |_) |  __/ || (_| |___) | |_) | (_| | (_|  __/
// |_|\_\_|  \___|\__,_|\__|_| \_/ |_|\__\__,_|\__|  \__|_|  |_|_| |_|  \__|   |_|\___|\___|_| |_|_| |_|_|_|\_\                    |____/ \___|\__\__,_|____/| .__/ \__,_|\___\___|
//                                                                                                                                                           |_|                   
// 

int dataCols = 176;
int dataRows = 6;
PROGMEM prog_uchar data[] = { "  \\/|  _ __  ____  _  _   / \\  __|_  ____  _ (_   / \\   |||  _  _   `|,  ____  _ (_   / \\    |    \\ /  _ )_  ____   '|.| _   _  |||| |\\ / __ )_ _____ _____ _ ___  /\\||  _  _   `|,  ____  _ (_   / \\  __|_  |_|_ _   \\  |\\/|  _ __  ____  _  _   / \\    |   )\\ / _  )_ _____ __ |_ _   _  ||||                                                                                                                          _/ \\  _ <_   / \\  || | _   _  )||| __  _  (|||   \\ _  _ ||  __     '||  _  _   |||   \\ _  _ ||  __    |'|| _   _  ||||  ____  ____  _ (_   / \\   \\/|  _ __  ____  |  _ __/ \\ _ ||| _   _ _ ||| __     |            | |  ____  |_|_ _   \\  |||  ____  _ | |  /  _  |||| ____  _ | |  /  _  )||| __  _  (|||  __    __     '||  _  _   |||  ____  |_|_ _   \\  |||          | |  ____  |_|_ _   \\  )||| __  _  (`|,  ____  ) (_ __/ \\  (_|_  |_|_ _   \\  )||| __  _  (/||  _ /    / /    V_   \\ \\  _ \\   )\\|| __  _  (|||  ____  |_|_ _   \\  ||||  _  _   `|,  ____  _ (_   / \\   \\/|  _ __  ____  _  _   / \\  __|   __     '||  _  _ _/||\\ _ /\\_  /  \\  |'.| _   _  |||| " };

	char inline dataChar(int x, int y) {
	    return pgm_read_byte_near(data + x * dataRows + y);
	}
	
int numTexts = 4;
int numChars[] = {320, 150, 100, 112};
int numRows[] = {13, 7, 7, 7};
int charOffsets[] = {0, 960, 1410, 1710};
PROGMEM prog_uchar charData[] = { "|\x03\x01_B\x02\\\x1c\n_\x1c\x01_9\x01_+\x02|\x08\x02/!\x08_*\n|I\x03_0\x04|,\x03_\x08\x00|\'\x03|\x15\x03(=\x01|\n\x04_\x0e\x04|%\x02/8\x08_\x10\x01\\\x08\x04\\\x06\x04_\x1f\x07_B\x00|G\x02_7\x02_\x14\x01_8\x07_7\x01_\x16\x04|\x05\x01_\x14\x03_\x1a\x04/#\x02(1\x07_\'\x02_\x0b\x02|A\x02_F\x03|\x1b\t_$\x01|I\x01\\5\x04|E\x02|K\x02|%\n|C\x02|\x1d\x03|2\x02/\r\x02_\t\x01`,\x02|6\x01`\x15\x02|\x03\x02/\x12\x02\\\r\x04/6\x08(\x13\x03|1\t<7\t_\x10\x03/\x08\x01\'\n\x02\':\x02_\x1e\n_(\x04|\'\t_\x07\x04_6\x02((\x01_*\x04|5\n_(\x08_\x16\x01|3\t|.\x04_\x1a\x06_>\x01_,\n|2\x04|+\x08\\\x11\x02_\x1e\t|4\x02|8\x03_\x07\x00|K\x04|\x03\x03_<\x01_5\x00_\x18\x00_\x0c\x02_\x18\x07_$\x04|C\x04|:\x03/)\x02_(\x07\\H\x04_2\x07_F\x02(*\x03/\x1c\x08|\x03\x04|\x17\x04|\x19\x03_&\x06_\t\x04.\x05\x03_I\x04\\0\x08_-\x04,\x15\x04|-\n_\x04\x04_\x1f\t|=\x03_2\n|\'\n|/\n|(\x03\\/\x04|%\x08)3\x07|\x1b\x02_B\x03_\x1c\x04_1\x01/ \t_\x0e\x01|\x1d\x07_\x1c\x00_\x0f\x03|%\x03_\x1c\x07|=\x04|\n\x03|1\n|\x17\x01_0\n_\x18\x06_D\x04_A\x00_J\x02_.\x07_\x19\x06_<\x02|\x0c\x03(,\x01\\\x1d\x02\\*\x08_+\x03(\x1b\x01|G\x03_7\n_)\x01|+\n|?\x04\\\x07\x03|6\x03|)\n_1\x04_\x1a\x02|?\x02|\x1b\x08_H\x00_>\x00_ \x04_J\x01_\'\x04|#\x03|5\x07_$\x08_$\n_\x04\x00_$\x07|\x08\x03_$\t_1\x03|\x1b\x03_\x1e\x01(#\x01)?\x01|\x17\x07/D\x01_F\x00|.\x02|.\x03)%\x01_&\x00/\x07\x02|)\t\\)\x04|0\x03|%\x07V \x03_\x14\x02_@\x04|\x17\x02|\x19\x01|4\x01/@\x01_J\x04|/\t_#\t_\x0f\x01|\x19\t_J\x03\\!\n_#\x07\'-\x08\\\x1f\x02|8\x04_)\x00_#\x08|\'\x07|C\x03\\\x1e\x03\\8\n|G\x01_+\x01| \n|?\x03_4\x06_\"\x07/\x11\x03_\x1e\x07_\x13\x01\\ \x08|\x19\x08_&\n/\"\x03|\x19\n\\&\x04|\x05\x04_\x13\x04_4\n_\x10\x04(\"\t\\\x18\x04_6\x04_\x1c\x06|4\x03|5\x08_\x14\x04_/\x00\'\x05\x02|#\x04_)\x07_\x0f\x04_E\x00|3\x08).\x01_I\x02_;\x01_/\x07|\x17\x03_\x1b\x06|3\n_#\n,,\x04_\"\n_\x1f\n\\\x12\x04_\x0c\x01_F\x01|1\x08_\"\x01/!\x02_\x1a\n_>\x04|C\x01\\\x1f\x04|\'\x01_\x1a\x01_\x0b\x01|\x11\x04|E\x04)\x1d\x01_(\x02_,\x07_\x0f\x02_+\x04|A\x04_7\x03/\x06\x01|+\t_B\x01|0\x01|\x1d\x04|8\x02|-\t|\x1b\n_.\x08/!\x04_\x1d\n\\6\n_-\x00|:\x04_7\x07_$\x00_\x1a\x03_\x19\x04_1\x02_;\x02_9\x04_-\x01_\x1e\x08|\x1b\x04)*\x01_7\x04|=\x02_0\x02_2\x06_\x19\x02|%\x04\'\'\x08|%\t|\x1e\x03|?\x04//\x04,\"\x04|*\x03_#\x01_=\x01_=\x03|$\x04|6\x04/)\x04/\x1f\x02_\x1e\x04|\x1b\x04_\x12\x00_\x18\x04_&\x01_\x13\x03_>\x01\\\x1c\x04_5\x01_3\x01_\x11\x00_\x12\x01/\x17\x02_(\x01_&\x00_5\x04\\\x17\x04.,\x04_%\x00|\x1d\x01).\x03_\x13\x02/?\x03_\x1d\x02_\x1a\x01/1\x02_!\x03_\x1c\x00_\x13\x00_-\x01_\x1e\x02\\/\x02|0\x03|*\x04\\)\x02|)\x01_%\x02_&\x04|\x16\x03|,\x03_-\x03\\?\x02_\x1d\x04_\x19\x04|*\x02_ \x04_!\x04_!\x01/;\x02_3\x03/\x1b\x03_>\x03_#\x04|\x10\x01_9\x04_(\x00_\x18\x01_=\x04_+\x05_!\x02_3\x04\\\x15\x02|\x10\x03_:\x01_\x19\x03,4\x04(8\x03_3\x02_\x19\x02|6\x02_\x19\x01)(\x03|\x1b\x01_\'\x01_=\x02\\\x1f\x04_-\x04/7\x02_2\x04_9\x01_\'\x00|4\x03|\"\x03|,\x05_\x14\x00_\x1a\x04_\'\x03|\x12\x03_\x1e\x01`4\x02( \x03|\x10\x04/$\x01_\x14\x04\\;\x04\\1\x04|\x10\x02|6\x03_-\x02_\x11\x04_&\x03_%\x04)\x15\x01_.\x04_9\x02_<\x01|:\x03/\x15\x04_\x13\x01_:\x04(2\x03_>\x04_2\x01_\x1a\x03_:\x02_%\x03\\$\x02\',\x02\\\x1b\x02_\x13\x04_+\x01_9\x03_<\x04_ \x01\\7\x04_.\x01|$\x03_(\x04_\'\x02_\'\x04|\x1d\x03_\x12\x04|*\x05`\"\x02)\x14\x03_8\x01_8\x04_&\x02|:\x03_(\x04_2\x01|4\x03_\'\x01\\\x1b\x03_7\x04\\\x1a\x04\\9\x02| \x03|&\x01\\\'\x04|0\x04\\\x1a\x02\\3\x02_7\x03_\x18\x00_+\x01_-\x01_6\x01_3\x04\\\x19\x01_ \x02_8\x01,*\x04_ \x01_\"\x04_#\x02_\x15\x04|&\x03|,\x04,$\x04_8\x04_1\x02|,\x03\\\x1c\x04_7\x02|$\x01_+\x04|$\x03_\x17\x03|\x1e\x03_\x18\x02_7\x01\'0\x02_%\x00_\"\x01|4\x04_#\x04_\x1d\x04|\x1e\x04/\x17\x01_#\x03_\x19\x03\\5\x04|&\x04_/\x01|\x1c\x02_)\x04/\x14\x04_\x1b\x04/\x15\x03|.\x02|.\x04_6\x04|*\x03(\"\x03_\x1f\x02|2\x04\\!\x04|(\x02/9\x04_\x18\x03|*\x02_1\x01|2\x03/\x16\x02|&\x02|\x1c\x03(,\x01/\x16\x04_-\x04|(\x03|,\x02\'\x1e\x02).\x01_%\x04_/\x04/!\x02`$\x02|.\x03_\x1f\x01|0\x03(6\x03)8\x03_-\x00_\x1d\x01_#\x01_)\x03/5\x02_\x15\x00_6\x04|7\x03_(\x02_\x18\x00|;\x01_)\x01_$\x02_0\x01_\x1f\x02_0\x02_%\x01_5\x04_(\x01|)\x03_,\x04|)\x04_\"\x04_\'\x01_:\x04_\x1d\x01_8\x01|-\x03|+\x02_\x17\x00\\*\x02|!\x04(+\x01`7\x02_6\x01_.\x04|!\x03)-\x01|9\x02_ \x01_\x1a\x01|-\x02_5\x01\\2\x02|%\x04|#\x03_\x1a\x04|;\x03|\x17\x04`&\x02|+\x04|\x15\x04\'#\x02_\x18\x01_\x1d\x04_\x1a\x02|\x19\x01|\x15\x02_6\x03|-\x04_&\x04|9\x01|/\x04_\x1b\x03_ \x02\\4\x04\\\x18\x04|3\x03|\'\x03/4\x02_$\x01|%\x03\'/\x02|9\x04_\x1b\x04_:\x00_*\x04|\x17\x03_\"\x01_\x16\x04|3\x04|\x1e\x04|\x1c\x04_,\x00|+\x03_8\x04|\x1e\x03|1\x03_\x14\x01_\x1f\x01|/\x03|9\x03|\x17\x02\\\x1c\x02/\x1c\x03|1\x04,7\x04_\x1a\x03_\x14\x00|\x13\x01_2\x04|;\x04|#\x04|\'\x04(5\x03_\x19\x04|;\x02/\x18\x02|!\x02_\x1b\x01_.\x01\'\x1e\x02|\x15\x03_1\x01_\x16\x00_6\x02_,\x01" };

	void inline randomDataChar(int textIdx, int charIdx, int *x, int *y, char *c) {

	    *c = pgm_read_byte_near(charData + charOffsets[textIdx] + charIdx * 3);
	    *x = pgm_read_byte_near(charData + charOffsets[textIdx] + charIdx * 3 + 1);
	    *y = pgm_read_byte_near(charData + charOffsets[textIdx] + charIdx * 3 + 2);
	}
	
