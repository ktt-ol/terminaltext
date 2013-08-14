//  _  __               _   _       _ _  _   _ _     _        _  __  __ _     _____         _           _ _                         __  __       _        __                          
// | |/ /_ __ ___  __ _| |_(_)_   _(_) |(_)_(_) |_  | |_ _ __(_)/ _|/ _| |_  |_   _|__  ___| |__  _ __ (_) | __                    |  \/  | __ _(_)_ __  / _|_ __ __ _ _ __ ___   ___ 
// | ' /| '__/ _ \/ _` | __| \ \ / / | __/ _` | __| | __| '__| | |_| |_| __|   | |/ _ \/ __| '_ \| '_ \| | |/ /                    | |\/| |/ _` | | '_ \| |_| '__/ _` | '_ ` _ \ / _ \
// | . \| | |  __/ (_| | |_| |\ V /| | || (_| | |_  | |_| |  | |  _|  _| |_    | |  __/ (__| | | | | | | |   <                     | |  | | (_| | | | | |  _| | | (_| | | | | | |  __/
// |_|\_\_|  \___|\__,_|\__|_| \_/ |_|\__\__,_|\__|  \__|_|  |_|_| |_|  \__|   |_|\___|\___|_| |_|_| |_|_|_|\_\                    |_|  |_|\__,_|_|_| |_|_| |_|  \__,_|_| |_| |_|\___|
//                                                                                                                                                                                    
// 

int dataCols = 179;
int dataRows = 5;
const PROGMEM char data[] = { "  \\/| _ __ ____ _  _  / \\   ||  \\ _ _ || __   _ ||  ` _ _ || __    '|| _  _  ||| _  _  `|, ____ _ (_  / \\ __|  __    '|| _  _ ||||____ _ | | /  _  |||  \\ _ _ || __    '|| _  _ )|||__  _ (||| _  _  `|, ____ _ (_  / \\ ||||_   __ ||| //   \\\\  _ |||_   _ ||||                                                                                                     _/ \\ _ <_  / \\ || |_   _ )|||__  _ (|||  \\ _ _ || __    '|| _  _  |||  \\ _ _ || __   |'||_   _ |||| ____ ____ _ (_  / \\  \\/| _ __ ____ |  ___/ \\_ |||_   __ |||__    |          | | ____ |_|__   \\ ||| ____ _ | | /  _ ||||____ _ | | /  _ )|||__  _ (||| __   __    '|| _  _  ||| ____ |_|__   \\ |||        | | ____ |_|__   \\ )|||__  _ (`|, ____ ) (___/ \\ (_|_ |_|__   \\ )|||__  _ (/|| _ /   / /   V_  \\ \\ _ \\  )\\||__  _ (||| ____ |_|__   \\ |||| _  _  `|, ____ _ (_  / \\  \\/| _ __ ____ _  _  / \\ __|  __    '|| _  __/||\\_ /\\_ /  \\ |'.|_   _ ||||" };

    char inline dataChar(int x, int y) {
        return pgm_read_byte_near(data + x * dataRows + y);
    }
    
//                __  __       _        __                          
//               |  \/  | __ _(_)_ __  / _|_ __ __ _ _ __ ___   ___ 
//               | |\/| |/ _` | | '_ \| |_| '__/ _` | '_ ` _ \ / _ \
//               | |  | | (_| | | | | |  _| | | (_| | | | | | |  __/
//               |_|  |_|\__,_|_|_| |_|_| |_|  \__,_|_| |_| |_|\___|
//                                                                  
// 
//                               _____                
//                              |_   _| __ ___  _ __  
//                                | || '__/ _ \| '_ \ 
//                                | || | | (_) | | | |
//                                |_||_|  \___/|_| |_|
//                                                    
// 
//    ____               ___  _     _            _                               
//   |  _ \  ___ _ __   / _ \| | __| | ___ _ __ | |__  _   _ _ __ __ _  ___ _ __ 
//   | | | |/ _ \ '__| | | | | |/ _` |/ _ \ '_ \| '_ \| | | | '__/ _` |/ _ \ '__|
//   | |_| |  __/ |    | |_| | | (_| |  __/ | | | |_) | |_| | | | (_| |  __/ |   
//   |____/ \___|_|     \___/|_|\__,_|\___|_| |_|_.__/ \__,_|_|  \__, |\___|_|   
//                                                               |___/           
//                  _   _            _                             
//                 | | | | __ _  ___| | _____ _ __   __ _  ___ ___ 
//                 | |_| |/ _` |/ __| |/ / __| '_ \ / _` |/ __/ _ \
//                 |  _  | (_| | (__|   <\__ \ |_) | (_| | (_|  __/
//                 |_| |_|\__,_|\___|_|\_\___/ .__/ \__,_|\___\___|
//                                           |_|                   
// 
//    _     _   _             ____               _        __                     
//   | |__ | |_| |_ _ __ _   / / / __ ___   __ _(_)_ __  / _|_ __ __ _ _ __ ___  
//   | '_ \| __| __| '_ (_) / / / '_ ` _ \ / _` | | '_ \| |_| '__/ _` | '_ ` _ \ 
//   | | | | |_| |_| |_) | / / /| | | | | | (_| | | | | |  _| | | (_| | | | | | |
//   |_| |_|\__|\__| .__(_)_/_/ |_| |_| |_|\__,_|_|_| |_|_| |_|  \__,_|_| |_| |_|
//                 |_|                                                           
//                                         _       
//                                   ___  (_) ___  
//                                  / _ \ | |/ _ \ 
//                                 |  __/_| | (_) |
//                                  \___(_)_|\___/ 
//                                                 
// 
int rnd_text_num = 4;
int rnd_text_chars[] = {142, 59, 352, 259};
int rnd_text_rows[] = {7, 7, 13, 13};
int rnd_text_char_offsets[] = {0, 426, 603, 1659};
const PROGMEM char rnd_text_char_data[] = { "|\x15\x04(\x17\x03/,\x02|!\x03|#\x03_ \x02_?\x04|\'\x03|\x1f\x03\\\x16\x04|5\x03_\x1c\x04(\x1b\x01\')\x02_>\x03_\x1e\x04|3\x04_ \x01|1\x04\\\"\x02_\x1e\x01_8\x01_\x18\x02/\x12\x01/\x16\x02\\,\x04|%\x02_0\x01_%\x00\\\x11\x01_-\x04|\x19\x03_8\x02|1\x03|\x10\x03|9\x04_4\x02_\x14\x00|!\x04_$\x04_2\x01_&\x01_\x0f\x04|\x0e\x03|\x15\x03_(\x04|\x1d\x04|9\x03_\x17\x01|)\x04_*\x02,/\x04|\'\x01|#\x02_&\x02_.\x01_\x17\x04|%\x04_=\x04_7\x01`6\x02_?\x01_0\x04|\x15\x01|\x10\x02_!\x01_5\x01_(\x01_.\x03_:\x04_*\x01\'\x1f\x02|\x13\x04_\"\x04|\x13\x02_?\x03_&\x00_>\x04/@\x03`/\x02_6\x04\\\x11\x02_>\x01`\x19\x02_\x18\x03|\x1d\x02|3\x03|\x0e\x01|\x10\x04,\x19\x04|+\x03_\x14\x04_+\x01_\x1a\x04|\x1b\x04_-\x01_>\x02/\x12\x02_\x1c\x00_\x18\x01|\x1b\x03_&\x03_\x1a\x01|;\x04\\@\x02_\x13\x00|;\x03/$\x01)\x1d\x01_9\x01|/\x03|@\x04|)\x03|\'\x04|7\x04|\x1d\x03_+\x02|#\x04(-\x03_2\x04|\'\x02\\:\x02_\x18\x04_\x10\x00|\x1f\x04|5\x04_\x1c\x01_.\x04\\<\x04_.\x02|\x15\x02_\x0f\x00\'3\x02_=\x01/<\x02|7\x03|\x13\x03_4\x01|\x0e\x02|1\x02|\x1b\x02|\x0e\x04_)\x02|\"\x04|#\x01_)\x03_!\x00_-\x01|0\x03|!\x03|2\x04\\+\x02|,\x04\\1\x02\\\'\x04_(\x01|.\x04_(\x04|0\x04_*\x01_#\x04_ \x04|\x1f\x02_\"\x00_1\x04\'.\x02_ \x00_\"\x01|,\x03|&\x03_)\x01_\x1e\x01|$\x04|\x1d\x01|2\x03|\"\x02|\x1f\x03\'$\x02_\x1e\x00|.\x03_/\x01|!\x02/+\x04_\x1f\x00|!\x04_%\x02|\x1f\x04_%\x01|,\x02((\x03|$\x03_-\x04/\'\x02_&\x02_&\x01)*\x03_/\x02_)\x04|\"\x03_0\x01_*\x04_9\t_\x19\x08_.\x07_\x10\x01_I\x04_\'\x07|!\x07|#\x08/\x15\x01| \x03|!\t/2\x04\\$\n_+\x0b_\x04\x00_+\x07|\x18\x02|5\x02_%\x02_@\x04_\x11\x02_3\n|!\x08\\H\x02`\x1a\x08_(\x04|\x16\t,7\x04|\x12\x02\\&\t_F\x01/7\x08| \x01_)\n_\x11\x01\\\t\x04\\/\x08_\x17\x04_-\n\\#\x04|)\x04(\x18\t\\D\x04_0\x03_F\x03/*\n|,\x0b|\x08\x02_\x05\x00|/\x01_>\x07_&\x03_:\x08\\\x15\x04_ \x08|7\x03_\x05\x01_:\x07_&\x07|#\x07|6\n, \x04_<\x02_\"\n_8\n_%\n_\x1f\x08/\x1d\x08|\x18\x03_@\x01|\x16\x03_\x1f\x03_1\x04_(\t_.\x00|\"\x02\\1\n|\x0f\x03_ \n_:\n|-\x04_?\x04|!\n_\x0b\x02|\x16\n_\x1f\t_\x15\n|?\n_\x11\n|J\x03|\x14\x02|M\x02,\x1a\n|\"\x01_\x19\t|\x1a\x02_3\t/B\x05(\x1e\t<%\t_*\x01|C\x02\'/\x02_1\x01_\x0b\x04_3\x07|\x10\x07|\x06\x02_=\x07_6\x04\\\x17\n_\x1f\n_\x05\x04_\x18\x04_%\x01_\x0b\x01|\x1c\n_\x1e\x04_\x10\x02\'J\x02\\\x1d\n|\x1c\x03_5\n_5\x04/1\x08/&\x08|\x1c\x02/\'\x03|6\t_\x1b\n\\\x19\x01|+\x03_9\x07|\x16\x07_\x15\x06\\\'\x02_%\x07_<\n|/\x03|\r\x04|\x06\x03_\x0c\x01/$\x08_(\x01|\x1c\x08_&\x01/\x07\x04|J\x04_?\x01_.\n_\x0c\x04_6\x03_$\x01_8\x07_\x1b\x04_\x19\n|7\x02_?\x05`A\x02/\x19\x04_\x1f\x04_<\x01_\x1b\x07_*\x02_\x18\x00_G\x01|\x02\x02` \x02\\\x07\x01|5\x03_\x16\x04(?\x03_\x1f\x02_+\x01|\x1c\x01_E\x04|\x14\x08_-\x08_ \x07|\x10\n|\x1c\x04_\x1e\x07_)\x08_<\x07/D\x02/?\t|\x02\x04|-\x01|\x1a\t).\t_5\x07_\x19\x07_=\x02_\x1f\x07\\7\n_\x1e\n.,\n\\?\x08_\x16\x00_9\n_=\n_-\x07_ \t_\x13\x08_\x1f\x01|C\x04|\x12\x08_B\x01_%\x03|>\x05_E\x01_=\x01_L\x01\\\r\x02_8\x04_\x0e\x01_:\x04_>\n|;\x04|*\x0b_\x17\x00|\x04\x03\',\x08(\x1e\x03_\x0b\x03|\x12\x07|=\x03|\x1c\t\';\x02_2\x07|\x14\x03|\x14\n\'\x0f\x02_\x03\x00_\x06\x04|H\x04|*\x08|#\n_K\x01_F\x04_\x03\x04_F\x02|\x1a\x01\')\x02_=\t|\x14\x07|\"\x03|\x04\x02(2\t//\n\\&\n|:\t|A\x03)1\x03\\;\n_\x13\t_\x05\x03\\>\x04\\,\x02|\x1a\x03_\x17\x03|\x16\x02_\x06\x00/>\x02_!\x04_&\x04\\*\t_\"\x06,4\n|\x16\x08_:\x01/\x17\x08_\x18\n_G\x03|3\x02_(\x08_!\x00_\n\x04_\x17\x01|\x08\x03_@\x05|\x1a\x04|)\x03_0\x04|\x02\x01_@\x03|\x0f\x04_L\x02_)\x07_\x11\x06|9\x03_0\x01|\'\x04_\'\t_>\t/H\x03(8\t\\2\x02_\x18\x07_(\x07|4\t/;\x08|\x02\x03_8\x01|-\x03\\\x1d\x04|;\x03_-\t|0\t_K\x02`4\x08_%\x04|-\x02,A\x04_(\n_=\x08|9\x04_4\x01_\x04\x04|9\x02_9\x08_G\x04/\r\x03_\x1b\x00_0\x02_\n\x01_\x1e\x01|C\x03_\'\n_$\x04_A\x05|+\x04_,\x04|\x10\t_I\x01_@\x02|6\x08|,\t_\x0c\x03|\x10\x08/\x1d\x02|\"\x04/#\x02|\x12\n_3\x08_\x0e\x04_2\n/\t\x02./\x04_.\x04\\4\x04|3\x03\'1\x02_$\x02_\n\x02|#\x04|-\x02\'E\x02_\x13\x03|\x0c\x01\\*\n_,\x01|)\x08_&\x04_#\x08|)\t|-\x04/>\x02|9\x01|5\x02_#\t_G\x01|-\x03_J\x01_#\n|3\x03|\x06\x04.\x12\x04|E\x04(?\x03_<\x01`+\x02|\x04\x01|\x04\x04_\r\x00_\x0b\x01\\(\x04_-\x07(\'\x07|;\x04|7\x04/(\x02_\x1a\x04_@\x01_\x1d\x00_:\x04|\x1d\x04)-\t_8\x00|K\x03_,\n|/\x02|\x10\x04|\n\x03|)\n|\'\x04_,\x08_=\x01_4\x04_&\t_0\x04_\x0f\x03)/\x01_D\x01\\>\x04\\.\x08_\x03\x00/\x1c\x01_\x13\x02|\x0c\x03_?\x01|5\x03/%\t|!\x03_,\x07(\x15\x04()\x03_8\x03_#\x07|\'\x03|\x10\x02|\x0e\x03_)\x01_$\t_\x0b\x02_K\x01|\x0c\x04|\x10\x05|/\t_?\x04_L\x04_:\x01|/\x03|#\x03_B\x04_.\x01_\"\n_\n\x04`A\x02_,\t_J\x02_)\x04| \t\\\t\x04_$\x01|G\x04_8\x02_$\x07/!\x08/\x1e\x01_,\x04\\L\x02(-\x01_*\x01_\x03\x04|I\x03_(\x06_.\x00|1\x04(+\t|%\x04|/\x04|\x08\x01)\'\n_6\x04|\'\t_I\x01|9\x02`H\x02|\x1d\x03(%\n_!\x01,+\x04/6\x01|M\x04|\x0c\x02_\x1b\x00_\x1e\x04_\x13\x01)\x14\x03_8\x01_<\x02|;\x03|\x02\x01_\x13\x04_.\x04/\x1a\x03|5\x04|G\x03/\x19\x02_@\x02|\x02\x04|M\x03/\x1b\x02\\\r\x04|\x08\x03_#\x01|\'\x08_(\x07_\x1e\x00_ \x02_\x18\x04_\x06\x01|1\x03_&\n_\x0e\x04/\x1b\x04_\x14\x01|\x10\x03|\x0e\x01_%\x01|9\x04|C\x02_\x11\x01\'\x04\x02_2\x01|+\x03|3\x04(\x15\x02_\x11\x05_F\x02|I\x04|\x1f\x04_*\x04|\x08\x04_B\x01|E\x03`\"\x02_\x0f\x04_ \x01_\x16\x02|K\x04_\x0f\x02\\%\x08|\x02\x02\\\x07\x02|C\x03/\x1c\x03|7\x02\\&\x02_3\x01_$\n|\x12\x03/\x1d\x02|\n\x01|\x02\x03_*\x02)\x17\x02_\x05\x02|\x12\x05\\!\n_\x0b\x03/\x19\x04|!\x04/\x18\x03_\"\x07_H\x04_@\x04|\x06\x03_\"\x04_\x0f\x01|9\x03)\x17\x04|\x04\x03/\x1a\x01_\x0e\x02|\x08\x02))\x07_\t\x00_7\x00_+\x07_D\x04_F\x01_\x16\x04_=\x02_@\x03_*\x03_+\n_\x1c\x00|\x1f\x03/*\x08|%\x03_2\x02_\x14\x04_\x07\x04_0\x01\'\x12\x02|C\x04|A\x03_\x0b\x04\';\x02\'\x1f\x02/.\n_\x05\x01|=\x03_(\n|\x16\x03\\4\x02_\x16\x01,A\x04_-\n" };

    void inline rnd_text_char(int textIdx, int charIdx, int *x, int *y, char *c) {

        *c = pgm_read_byte_near(rnd_text_char_data + rnd_text_char_offsets[textIdx] + charIdx * 3);
        *x = pgm_read_byte_near(rnd_text_char_data + rnd_text_char_offsets[textIdx] + charIdx * 3 + 1);
        *y = pgm_read_byte_near(rnd_text_char_data + rnd_text_char_offsets[textIdx] + charIdx * 3 + 2);
    }
    