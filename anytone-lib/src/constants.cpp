#include "constants.h"
const QString Constants::CPS_VERISON = "0.1";
const QString Constants::CPS_BUILD_NUMBER = "8";
const QStringList Constants::OFF_ON = {"Off", "On"};
const QStringList Constants::VF_MR = {"MEM", "VFO"};
const QStringList Constants::AT_OPTIONS = {
    "MODE 00000 Rx:400-480 136-174 Tx:400-480 136-174", 
    "MODE 00001 Rx:400-480 136-174 Tx:400-480 136-174 (12.5KHz Only)", 
    "MODE 00002 Rx:430-440 136-174 Tx:430-440 136-174", 
    "MODE 00003 Rx:400-480 136-174 Tx:430-440 144-146", 
    "MODE 00004 Rx:434-438 144-146 Tx:434-438 144-146", 
    "MODE 00005 Rx:434-447 144-146 Tx:434-447 144-146", 
    "MODE 00006 Rx:446-447 136-174 Tx:446-447 136-174", 
    "MODE 00007 Rx:400-480 136-174 Tx:420-450 144-148", 
    "MODE 00008 Rx:400-470 136-174 Tx:400-470 136-174", 
    "MODE 00009 Rx:430-432 144-146 Tx:430-432 144-146", 
    "MODE 00010 Rx:400-480 136-174 Tx:430-450 144-148", 
    "MODE 00011 Rx:400-520 136-174 Tx:400-520 136-174", 
    "MODE 00012 Rx:400-490 136-174 Tx:400-490 136-174", 
    "MODE 00013 Rx:400-480 136-174 Tx:403-470 136-174", 
    "MODE 00014 Rx:400-520 220-225 136-174 Tx:400-520 220-225 136-174", 
    "MODE 00015 Rx:420-520 144-148 Tx:420-520 144-148", 
    "MODE 00016 Rx:430-440 144-147 Tx:430-440 144-147", 
    "MODE 00017 Rx:430-440 136-174 Tx:136-174", 
    "MODE 00018 Rx:400-480 220-225 136-174 Tx:420-450 222-225 144-148"
};
const QStringList Constants::CHANNEL_TYPE = {"A-Analog", "D-Digital", "A+D TX A", "D+A TX D"};
const QStringList Constants::TX_POWER = {"Low", "Mid", "High", "Turbo"};
const QStringList Constants::BAND_WIDTH = {"12.5K", "25K"};
const QStringList Constants::CTCSS_CODE = {
    "62.5", "67.0", "69.3", "71.9", "74.4", "77.0", "79.7", "82.5", 
    "85.4", "88.5", "91.5", "94.8", "97.4", "100.0", "103.5", "107.2", 
    "110.9", "114.8", "118.8", "123.0", "127.3", "131.8", "136.5", "141.3", 
    "146.2", "151.4", "156.7", "159.8", "162.2", "165.5", "167.9", "171.3", 
    "173.8", "177.3", "179.9", "183.5", "186.2", "189.9", "192.8", "196.6", 
    "199.5", "203.5", "206.5", "210.7", "218.1", "225.7", "229.1", "233.6", 
    "241.8", "250.3", "254.1", "Custom CTCSS"
};
const QStringList Constants::DCS_CODE = {
    "D000N", "D001N", "D002N", "D003N", "D004N", "D005N", "D006N", "D007N",
    "D010N", "D011N", "D012N", "D013N", "D014N", "D015N", "D016N", "D017N",
    "D020N", "D021N", "D022N", "D023N", "D024N", "D025N", "D026N", "D027N",
    "D030N", "D031N", "D032N", "D033N", "D034N", "D035N", "D036N", "D037N",
    "D040N", "D041N", "D042N", "D043N", "D044N", "D045N", "D046N", "D047N",
    "D050N", "D051N", "D052N", "D053N", "D054N", "D055N", "D056N", "D057N",
    "D060N", "D061N", "D062N", "D063N", "D064N", "D065N", "D066N", "D067N",
    "D070N", "D071N", "D072N", "D073N", "D074N", "D075N", "D076N", "D077N",
    "D100N", "D101N", "D102N", "D103N", "D104N", "D105N", "D106N", "D107N",
    "D110N", "D111N", "D112N", "D113N", "D114N", "D115N", "D116N", "D117N",
    "D120N", "D121N", "D122N", "D123N", "D124N", "D125N", "D126N", "D127N",
    "D130N", "D131N", "D132N", "D133N", "D134N", "D135N", "D136N", "D137N",
    "D140N", "D141N", "D142N", "D143N", "D144N", "D145N", "D146N", "D147N",
    "D150N", "D151N", "D152N", "D153N", "D154N", "D155N", "D156N", "D157N",
    "D160N", "D161N", "D162N", "D163N", "D164N", "D165N", "D166N", "D167N",
    "D170N", "D171N", "D172N", "D173N", "D174N", "D175N", "D176N", "D177N",
    "D200N", "D201N", "D202N", "D203N", "D204N", "D205N", "D206N", "D207N",
    "D210N", "D211N", "D212N", "D213N", "D214N", "D215N", "D216N", "D217N",
    "D220N", "D221N", "D222N", "D223N", "D224N", "D225N", "D226N", "D227N",
    "D230N", "D231N", "D232N", "D233N", "D234N", "D235N", "D236N", "D237N",
    "D240N", "D241N", "D242N", "D243N", "D244N", "D245N", "D246N", "D247N",
    "D250N", "D251N", "D252N", "D253N", "D254N", "D255N", "D256N", "D257N",
    "D260N", "D261N", "D262N", "D263N", "D264N", "D265N", "D266N", "D267N",
    "D270N", "D271N", "D272N", "D273N", "D274N", "D275N", "D276N", "D277N",
    "D300N", "D301N", "D302N", "D303N", "D304N", "D305N", "D306N", "D307N",
    "D310N", "D311N", "D312N", "D313N", "D314N", "D315N", "D316N", "D317N",
    "D320N", "D321N", "D322N", "D323N", "D324N", "D325N", "D326N", "D327N",
    "D330N", "D331N", "D332N", "D333N", "D334N", "D335N", "D336N", "D337N",
    "D340N", "D341N", "D342N", "D343N", "D344N", "D345N", "D346N", "D347N",
    "D350N", "D351N", "D352N", "D353N", "D354N", "D355N", "D356N", "D357N",
    "D360N", "D361N", "D362N", "D363N", "D364N", "D365N", "D366N", "D367N",
    "D370N", "D371N", "D372N", "D373N", "D374N", "D375N", "D376N", "D377N",
    "D400N", "D401N", "D402N", "D403N", "D404N", "D405N", "D406N", "D407N",
    "D410N", "D411N", "D412N", "D413N", "D414N", "D415N", "D416N", "D417N",
    "D420N", "D421N", "D422N", "D423N", "D424N", "D425N", "D426N", "D427N",
    "D430N", "D431N", "D432N", "D433N", "D434N", "D435N", "D436N", "D437N",
    "D440N", "D441N", "D442N", "D443N", "D444N", "D445N", "D446N", "D447N",
    "D450N", "D451N", "D452N", "D453N", "D454N", "D455N", "D456N", "D457N",
    "D460N", "D461N", "D462N", "D463N", "D464N", "D465N", "D466N", "D467N",
    "D470N", "D471N", "D472N", "D473N", "D474N", "D475N", "D476N", "D477N",
    "D500N", "D501N", "D502N", "D503N", "D504N", "D505N", "D506N", "D507N",
    "D510N", "D511N", "D512N", "D513N", "D514N", "D515N", "D516N", "D517N",
    "D520N", "D521N", "D522N", "D523N", "D524N", "D525N", "D526N", "D527N",
    "D530N", "D531N", "D532N", "D533N", "D534N", "D535N", "D536N", "D537N",
    "D540N", "D541N", "D542N", "D543N", "D544N", "D545N", "D546N", "D547N",
    "D550N", "D551N", "D552N", "D553N", "D554N", "D555N", "D556N", "D557N",
    "D560N", "D561N", "D562N", "D563N", "D564N", "D565N", "D566N", "D567N",
    "D570N", "D571N", "D572N", "D573N", "D574N", "D575N", "D576N", "D577N",
    "D600N", "D601N", "D602N", "D603N", "D604N", "D605N", "D606N", "D607N",
    "D610N", "D611N", "D612N", "D613N", "D614N", "D615N", "D616N", "D617N",
    "D620N", "D621N", "D622N", "D623N", "D624N", "D625N", "D626N", "D627N",
    "D630N", "D631N", "D632N", "D633N", "D634N", "D635N", "D636N", "D637N",
    "D640N", "D641N", "D642N", "D643N", "D644N", "D645N", "D646N", "D647N",
    "D650N", "D651N", "D652N", "D653N", "D654N", "D655N", "D656N", "D657N",
    "D660N", "D661N", "D662N", "D663N", "D664N", "D665N", "D666N", "D667N",
    "D670N", "D671N", "D672N", "D673N", "D674N", "D675N", "D676N", "D677N",
    "D700N", "D701N", "D702N", "D703N", "D704N", "D705N", "D706N", "D707N",
    "D710N", "D711N", "D712N", "D713N", "D714N", "D715N", "D716N", "D717N",
    "D720N", "D721N", "D722N", "D723N", "D724N", "D725N", "D726N", "D727N",
    "D730N", "D731N", "D732N", "D733N", "D734N", "D735N", "D736N", "D737N",
    "D740N", "D741N", "D742N", "D743N", "D744N", "D745N", "D746N", "D747N",
    "D750N", "D751N", "D752N", "D753N", "D754N", "D755N", "D756N", "D757N",
    "D760N", "D761N", "D762N", "D763N", "D764N", "D765N", "D766N", "D767N",
    "D770N", "D771N", "D772N", "D773N", "D774N", "D775N", "D776N", "D777N",
    "D000I", "D001I", "D002I", "D003I", "D004I", "D005I", "D006I", "D007I",
    "D010I", "D011I", "D012I", "D013I", "D014I", "D015I", "D016I", "D017I",
    "D020I", "D021I", "D022I", "D023I", "D024I", "D025I", "D026I", "D027I",
    "D030I", "D031I", "D032I", "D033I", "D034I", "D035I", "D036I", "D037I",
    "D040I", "D041I", "D042I", "D043I", "D044I", "D045I", "D046I", "D047I",
    "D050I", "D051I", "D052I", "D053I", "D054I", "D055I", "D056I", "D057I",
    "D060I", "D061I", "D062I", "D063I", "D064I", "D065I", "D066I", "D067I",
    "D070I", "D071I", "D072I", "D073I", "D074I", "D075I", "D076I", "D077I",
    "D100I", "D101I", "D102I", "D103I", "D104I", "D105I", "D106I", "D107I",
    "D110I", "D111I", "D112I", "D113I", "D114I", "D115I", "D116I", "D117I",
    "D120I", "D121I", "D122I", "D123I", "D124I", "D125I", "D126I", "D127I",
    "D130I", "D131I", "D132I", "D133I", "D134I", "D135I", "D136I", "D137I",
    "D140I", "D141I", "D142I", "D143I", "D144I", "D145I", "D146I", "D147I",
    "D150I", "D151I", "D152I", "D153I", "D154I", "D155I", "D156I", "D157I",
    "D160I", "D161I", "D162I", "D163I", "D164I", "D165I", "D166I", "D167I",
    "D170I", "D171I", "D172I", "D173I", "D174I", "D175I", "D176I", "D177I",
    "D200I", "D201I", "D202I", "D203I", "D204I", "D205I", "D206I", "D207I",
    "D210I", "D211I", "D212I", "D213I", "D214I", "D215I", "D216I", "D217I",
    "D220I", "D221I", "D222I", "D223I", "D224I", "D225I", "D226I", "D227I",
    "D230I", "D231I", "D232I", "D233I", "D234I", "D235I", "D236I", "D237I",
    "D240I", "D241I", "D242I", "D243I", "D244I", "D245I", "D246I", "D247I",
    "D250I", "D251I", "D252I", "D253I", "D254I", "D255I", "D256I", "D257I",
    "D260I", "D261I", "D262I", "D263I", "D264I", "D265I", "D266I", "D267I",
    "D270I", "D271I", "D272I", "D273I", "D274I", "D275I", "D276I", "D277I",
    "D300I", "D301I", "D302I", "D303I", "D304I", "D305I", "D306I", "D307I",
    "D310I", "D311I", "D312I", "D313I", "D314I", "D315I", "D316I", "D317I",
    "D320I", "D321I", "D322I", "D323I", "D324I", "D325I", "D326I", "D327I",
    "D330I", "D331I", "D332I", "D333I", "D334I", "D335I", "D336I", "D337I",
    "D340I", "D341I", "D342I", "D343I", "D344I", "D345I", "D346I", "D347I",
    "D350I", "D351I", "D352I", "D353I", "D354I", "D355I", "D356I", "D357I",
    "D360I", "D361I", "D362I", "D363I", "D364I", "D365I", "D366I", "D367I",
    "D370I", "D371I", "D372I", "D373I", "D374I", "D375I", "D376I", "D377I",
    "D400I", "D401I", "D402I", "D403I", "D404I", "D405I", "D406I", "D407I",
    "D410I", "D411I", "D412I", "D413I", "D414I", "D415I", "D416I", "D417I",
    "D420I", "D421I", "D422I", "D423I", "D424I", "D425I", "D426I", "D427I",
    "D430I", "D431I", "D432I", "D433I", "D434I", "D435I", "D436I", "D437I",
    "D440I", "D441I", "D442I", "D443I", "D444I", "D445I", "D446I", "D447I",
    "D450I", "D451I", "D452I", "D453I", "D454I", "D455I", "D456I", "D457I",
    "D460I", "D461I", "D462I", "D463I", "D464I", "D465I", "D466I", "D467I",
    "D470I", "D471I", "D472I", "D473I", "D474I", "D475I", "D476I", "D477I",
    "D500I", "D501I", "D502I", "D503I", "D504I", "D505I", "D506I", "D507I",
    "D510I", "D511I", "D512I", "D513I", "D514I", "D515I", "D516I", "D517I",
    "D520I", "D521I", "D522I", "D523I", "D524I", "D525I", "D526I", "D527I",
    "D530I", "D531I", "D532I", "D533I", "D534I", "D535I", "D536I", "D537I",
    "D540I", "D541I", "D542I", "D543I", "D544I", "D545I", "D546I", "D547I",
    "D550I", "D551I", "D552I", "D553I", "D554I", "D555I", "D556I", "D557I",
    "D560I", "D561I", "D562I", "D563I", "D564I", "D565I", "D566I", "D567I",
    "D570I", "D571I", "D572I", "D573I", "D574I", "D575I", "D576I", "D577I",
    "D600I", "D601I", "D602I", "D603I", "D604I", "D605I", "D606I", "D607I",
    "D610I", "D611I", "D612I", "D613I", "D614I", "D615I", "D616I", "D617I",
    "D620I", "D621I", "D622I", "D623I", "D624I", "D625I", "D626I", "D627I",
    "D630I", "D631I", "D632I", "D633I", "D634I", "D635I", "D636I", "D637I",
    "D640I", "D641I", "D642I", "D643I", "D644I", "D645I", "D646I", "D647I",
    "D650I", "D651I", "D652I", "D653I", "D654I", "D655I", "D656I", "D657I",
    "D660I", "D661I", "D662I", "D663I", "D664I", "D665I", "D666I", "D667I",
    "D670I", "D671I", "D672I", "D673I", "D674I", "D675I", "D676I", "D677I",
    "D700I", "D701I", "D702I", "D703I", "D704I", "D705I", "D706I", "D707I",
    "D710I", "D711I", "D712I", "D713I", "D714I", "D715I", "D716I", "D717I",
    "D720I", "D721I", "D722I", "D723I", "D724I", "D725I", "D726I", "D727I",
    "D730I", "D731I", "D732I", "D733I", "D734I", "D735I", "D736I", "D737I",
    "D740I", "D741I", "D742I", "D743I", "D744I", "D745I", "D746I", "D747I",
    "D750I", "D751I", "D752I", "D753I", "D754I", "D755I", "D756I", "D757I",
    "D760I", "D761I", "D762I", "D763I", "D764I", "D765I", "D766I", "D767I",
    "D770I", "D771I", "D772I", "D773I", "D774I", "D775I", "D776I", "D777I"
};
const QStringList Constants::ANALOG_APRS_PTT_MODE = {"Off", "Start of Transmission", "End of Transmission"};
const QStringList Constants::APRS_REPORT_TYPE = {"Off", "Analog", "Digital"};
const QStringList Constants::OPTIONAL_SIGNAL = {"Off", "DTMF", "2Tone", "5Tone"};
const QStringList Constants::CALL_TYPE = {"Private Call", "Group Call", "All Call"};
const QStringList Constants::CALL_ALERT = {"None", "Online Alert"};
const QStringList Constants::SCAN_LIST_PRIORITY_CHANNEL_SELECT {
    "Off",
    "Priority Channel Select1",
    "Priority Channel Select2",
    "Priority Channel Select1 + Priority Channel Select2"
};
const QStringList Constants::SCAN_LIST_PRIORITY_CHANNEL = {"Off", "Current Channel"};
const QStringList Constants::SCAN_LIST_REVERT_CHANNEL = {"Selected", "Selected + TalkBack", "Last Called", "Last Used"};
const QStringList Constants::SCAN_LIST_LOOK_BACK_TIME {
    "0.5", "0.6", "0.7", "0.8", "0.9", "1.0", "1.1", "1.2", "1.3", "1.4", "1.5", "1.6", "1.7", "1.8", "1.9", "2.0", 
    "2.1", "2.2", "2.3", "2.4", "2.5", "2.6", "2.7", "2.8", "2.9", "3.0", "3.1", "3.2", "3.3", "3.4", "3.5", "3.6", 
    "3.7", "3.8", "3.9", "4.0", "4.1", "4.2", "4.3", "4.4", "4.5", "4.6", "4.7", "4.8", "4.9"
};
const QStringList Constants::SCAN_LIST_DROPOUT_DELAY_DWELL_TIME {
    "0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1.0", "1.1", "1.2", "1.3", "1.4", "1.5", "1.6", 
    "1.7", "1.8", "1.9", "2.0", "2.1", "2.2", "2.3", "2.4", "2.5", "2.6", "2.7", "2.8", "2.9", "3.0", "3.1", "3.2", 
    "3.3", "3.4", "3.5", "3.6", "3.7", "3.8", "3.9", "4.0", "4.1", "4.2", "4.3", "4.4", "4.5", "4.6", "4.7", "4.8", 
    "4.9"
};
const QStringList Constants::SQL_MODE = {"Carrier", "CTCSS/DCS"};
const QStringList Constants::BUSY_LOCK = {"Off", "Different CDT", "Channel Free"};
const QStringList Constants::PTT_ID = {"Off", "Start", "End", "Start&End"};



const QStringList Constants::POWERON_INTERFACE = {"Default Interface", "Custom Char", "Custom Picture"};
const QStringList Constants::AUTOSHUTDOWN = {"Off", "10m", "30m", "60m", "120m"};
const QStringList Constants::POWER_SAVE = {"Off", "1:1", "2:1"};
const QStringList Constants::AUTOSHUTDOWN_TYPE = {"is affected by call", "is not affected by call"};
const QStringList Constants::BRIGHTNESS = {"1", "2", "3", "4", "5"};
const QStringList Constants::AUTO_BACKLIGHT_DURATION = {"Always", "5s", "10s", "15s", "20s", "25s", "30s", "1m", "2m", "3m", "4m", "5m", "15m", "30m", "45m", "60m"};
const QStringList Constants::BACKLIGHT_DELAY_TX = {
    "Off", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", 
    "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"
};
const QStringList Constants::MENU_EXIT_TIME = {"5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60"};
const QStringList Constants::LAST_CALLER = {"Off", "Display ID", "Display Callsign", "Show Both"};
const QStringList Constants::CALL_DISPLAY_MODE = {"Turn off Talker Alias", "Call Sign Based", "Name Based"};
const QStringList Constants::COLOR1 = {"Orange", "Red", "Yellow", "Green", "Turquiose", "Blue", "White"};
const QStringList Constants::COLOR2 = {"White", "Black", "Orange", "Red", "Yellow", "Green", "Turquiose", "Blue"};
const QStringList Constants::DISPLAY_CHANNEL_NUMBER = {"Actual Channel Number", "Sequence Number In Zone"};
const QStringList Constants::DISPLAY_STANDBY_PICTURE = {"Default", "Custom1", "Custom2"};
const QStringList Constants::BACKLIGHT_DELAY_RX = {
    "Always", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", 
    "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"
};
const QStringList Constants::DATE_DISPLAY_FORMAT = {"yyyy/m/d", "d/m/yyyy"};
const QStringList Constants::DISPLAY_MODE = {"Channel", "Frequency"};
const QStringList Constants::MAIN_CHANNEL_SET = {"A", "B"};
const QStringList Constants::WORKING_MODE = {"Amateur", "Professional"};
const QStringList Constants::VOX_LEVEL = {"Off", "1", "2", "3"};
const QStringList Constants::VOX_DELAY = {
    "0.5s", "0.6s", "0.7s", "0.8s", "0.9s", "1.0s", "1.1s", "1.2s", "1.3s", "1.4s", "1.5s", "1.6s", "1.7s", "1.8s", "1.9s", "2.0s", 
    "2.1s", "2.2s", "2.3s", "2.4s", "2.5s", "2.6s", "2.7s", "2.8s", "2.9s"
};
const QStringList Constants::VOX_DETECTION = {"Built-in Microphone", "External Microphone", "Both"};
const QStringList Constants::BT_GAIN = {"1", "2", "3", "4", "5"};
const QStringList Constants::BT_HOLD_TIME = {
    "Off", "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "11s", "12s", "13s", "14s", "15s", 
    "16s", "17s", "18s", "19s", "20s", "21s", "22s", "23s", "24s", "25s", "26s", "27s", "28s", "29s", "30s", "60s", 
    "120s", "Infinite"
};
const QStringList Constants::BT_RX_DELAY = {"30ms", "1.0s", "1.5s", "2.0s", "2.5s", "3.0s", "3.5s", "4.0s", "4.5s", "5.0s", "5.5s"};
const QStringList Constants::BT_PTT_SLEEP = {"Infinity", "1min", "2min", "3min", "4min"};
const QStringList Constants::STE_CTCSS_TYPE = {"Off", "Silent", "120 Degree", "180 Degree", "240 Degree"};
const QStringList Constants::STE_NO_SIGNAL = {"Off", "55.2Hz", "259.2Hz"};
const QStringList Constants::STE_TIME = {
    "10MS", "20MS", "30MS", "40MS", "50MS", "60MS", "70MS", "80MS", "90MS", "100MS", "110MS", "120MS", "130MS", "140MS", "150MS", "160MS", 
    "170MS", "180MS", "190MS", "200MS", "210MS", "220MS", "230MS", "240MS", "250MS", "260MS", "270MS", "280MS", "290MS", "300MS", "310MS", "320MS", 
    "330MS", "340MS", "350MS", "360MS", "370MS", "380MS", "390MS", "400MS", "410MS", "420MS", "430MS", "440MS", "450MS", "460MS", "470MS", "480MS", 
    "490MS", "500MS", "510MS", "520MS", "530MS", "540MS", "550MS", "560MS", "570MS", "580MS", "590MS", "600MS", "610MS", "620MS", "630MS", "640MS", 
    "650MS", "660MS", "670MS", "680MS", "690MS", "700MS", "710MS", "720MS", "730MS", "740MS", "750MS", "760MS", "770MS", "780MS", "790MS", "800MS", 
    "810MS", "820MS", "830MS", "840MS", "850MS", "860MS", "870MS", "880MS", "890MS", "900MS", "910MS", "920MS", "930MS", "940MS", "950MS", "960MS", 
    "970MS", "980MS", "990MS"
};
const QStringList Constants::KEY_LOCK = {"Manual", "Auto"};
const QStringList Constants::KEY_FUNCTION_D878UVII = {
    "Off", "Voltage", "Power", "Talk Around", "Reverse", "Digital Encryption", "Call", "VOX", "V/M", "Sub PTT", "Scan", "FM", "Alarm", "Record Switch", "Record", "SMS", 
    "Dial", "GPS Information", "Monitor", "Main Channel Switch", "Hot Key 1", "Hot Key 2", "Hot Key 3", "Hot Key 4", "Hot Key 5", "Hot Key 6", "Work Alone", "Nuisance Delete", "Digital Monitor", "Sub CH Switch", "Priority Zone", "VFO Scan", 
    "Mic Sound Quality", "Last Call Reply", "Channel Type Switch", "Ranging", "Roaming", "Channel Ranging", "Max Volume", "Slot Switch", "APRS Type Switch", "Zone Select", "Time Roaming Set", "APRS Set", "Mute Timing", "CTC/DCS Set", "TBST Send", "BT Wireless", 
    "GPS", "Ch. Name", "CDT Scan", "APRS Send", "Ana APRS Info", "GPS Roaming", "Dim Shut", "Satellite Predicting", "ANA SQL"
};
const QStringList Constants::KEY_FUNCTION_D890UV = {
    "Off", "Voltage", "Power", "Talk Around", "Reverse", "Digital Encryption", "Call", "VOX", "V/M", "Sub PTT", "Scan", "FM", "Alarm", "Record Switch", "Record", "SMS", 
    "Dial", "GPS Information", "Monitor", "Main Channel Switch", "Hot Key 1", "Hot Key 2", "Hot Key 3", "Hot Key 4", "Hot Key 5", "Hot Key 6", "Work Alone", "Nuisance Delete", "Digital Monitor", "Sub CH Switch", "Priority Zone", "VFO Scan", 
    "Mic Sound Quality", "Last Call Reply", "Channel Type Switch", "Ranging", "Roaming", "Channel Ranging", "Max Volume", "Slot Switch", "APRS Type Switch", "Zone Select", "Time Roaming Set", "APRS Set", "Mute Timing", "CTC/DCS Set", "TBST Send", "BT Wireless", 
    "GPS", "Ch. Name", "CDT Scan", "APRS Send", "Ana APRS Info", "GPS Roaming", "Dim Shut", "Satellite Predicting", "Sq Level", "NOAA", "CH Settings", "RX NR", "TX NR", "Repeater"
};
const QStringList Constants::LONG_KEY_TIME = {"1", "2", "3", "4", "5"};
const QStringList Constants::TOT = {"Off", "30s", "60s", "90s", "120s", "150s", "180s", "210s", "240s"};
const QStringList Constants::LANGUAGE = {"English", "German"};
const QStringList Constants::FREQUENCY_STEP = {"2.5K", "5K", "6.25K", "8.33K", "10K", "12.5K", "20K", "25K", "30K", "50K"};
const QStringList Constants::SQL_LEVEL = {"OFF", "1", "2", "3", "4", "5"};
const QStringList Constants::TBST = {"1000Hz", "1450Hz", "1750Hz", "2100Hz"};
const QStringList Constants::ANALOG_CALL_HOLD_TIME = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", 
    "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29"
};
const QStringList Constants::MUTE_TIMING = {
    "1minute", "2minute", "3minute", "4minute", "5minute", "6minute", "7minute", "8minute", "9minute", "10minute", "11minute", "12minute", "13minute", "14minute", "15minute", "16minute", 
    "17minute", "18minute", "19minute", "20minute", "21minute", "22minute", "23minute", "24minute", "25minute", "26minute", "27minute", "28minute", "29minute", "30minute", "31minute", "32minute", 
    "33minute", "34minute", "35minute", "36minute", "37minute", "38minute", "39minute", "40minute", "41minute", "42minute", "43minute", "44minute", "45minute", "46minute", "47minute", "48minute", 
    "49minute", "50minute", "51minute", "52minute", "53minute", "54minute", "55minute", "56minute", "57minute", "58minute", "59minute", "60minute", "61minute", "62minute", "63minute", "64minute", 
    "65minute", "66minute", "67minute", "68minute", "69minute", "70minute", "71minute", "72minute", "73minute", "74minute", "75minute", "76minute", "77minute", "78minute", "79minute", "80minute", 
    "81minute", "82minute", "83minute", "84minute", "85minute", "86minute", "87minute", "88minute", "89minute", "90minute", "91minute", "92minute", "93minute", "94minute", "95minute", "96minute", 
    "97minute", "98minute", "99minute", "100minute", "101minute", "102minute", "103minute", "104minute", "105minute", "106minute", "107minute", "108minute", "109minute", "110minute", "111minute", "112minute", 
    "113minute", "114minute", "115minute", "116minute", "117minute", "118minute", "119minute", "120minute", "121minute", "122minute", "123minute", "124minute", "125minute", "126minute", "127minute", "128minute", 
    "129minute", "130minute", "131minute", "132minute", "133minute", "134minute", "135minute", "136minute", "137minute", "138minute", "139minute", "140minute", "141minute", "142minute", "143minute", "144minute", 
    "145minute", "146minute", "147minute", "148minute", "149minute", "150minute", "151minute", "152minute", "153minute", "154minute", "155minute", "156minute", "157minute", "158minute", "159minute", "160minute", 
    "161minute", "162minute", "163minute", "164minute", "165minute", "166minute", "167minute", "168minute", "169minute", "170minute", "171minute", "172minute", "173minute", "174minute", "175minute", "176minute", 
    "177minute", "178minute", "179minute", "180minute", "181minute", "182minute", "183minute", "184minute", "185minute", "186minute", "187minute", "188minute", "189minute", "190minute", "191minute", "192minute", 
    "193minute", "194minute", "195minute", "196minute", "197minute", "198minute", "199minute", "200minute", "201minute", "202minute", "203minute", "204minute", "205minute", "206minute", "207minute", "208minute", 
    "209minute", "210minute", "211minute", "212minute", "213minute", "214minute", "215minute", "216minute", "217minute", "218minute", "219minute", "220minute", "221minute", "222minute", "223minute", "224minute", 
    "225minute", "226minute", "227minute", "228minute", "229minute", "230minute", "231minute", "232minute", "233minute", "234minute", "235minute", "236minute", "237minute", "238minute", "239minute", "240minute", 
    "241minute", "242minute", "243minute", "244minute", "245minute", "246minute", "247minute", "248minute", "249minute", "250minute", "251minute", "252minute", "253minute", "254minute", "255minute"
};
const QStringList Constants::ENCRYPTION_TYPE = {"Common", "Extended"};
const QStringList Constants::TG_HOLD_TIME = {
    "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "11s", "12s", "13s", "14s", "15s", "16s", 
    "17s", "18s", "19s", "20s", "21s", "22s", "23s", "24s", "25s", "26s", "27s", "28s", "29s", "30s", "30min", "Infinite"
};
const QStringList Constants::VOICE_HEADER_REPETITIONS = {"2", "3", "4", "5", "6", "7"};
const QStringList Constants::TX_PREAMBLE_DURATION = {
    "0ms", "60ms", "120ms", "180ms", "240ms", "300ms", "360ms", "420ms", "480ms", "540ms", "600ms", "660ms", "720ms", "780ms", "840ms", "900ms", 
    "960ms", "1020ms", "1080ms", "1140ms", "1200ms", "1260ms", "1320ms", "1380ms", "1440ms", "1500ms", "1560ms", "1620ms", "1680ms", "1740ms", "1800ms", "1860ms", 
    "1920ms", "1980ms", "2040ms", "2100ms", "2160ms", "2220ms", "2280ms", "2340ms"
};
const QStringList Constants::DIGITAL_MONITOR = {"Off", "Single Slot", "Double Slot"};
const QStringList Constants::DIGITAL_MONITOR_CC = {"Any", "Same"};
const QStringList Constants::SMS_FORMAT = {"M-SMS", "H-SMS", "DMR Standard", "Customer DMR"};
const QStringList Constants::ALERT = {"None", "Ring"};
const QStringList Constants::TALK_PERMIT = {"Off", "Digital", "Analog", "Digital & Analog"};
const QStringList Constants::DIGITAL_IDLE_TONE = {"Off", "Type 1", "Type 2", "Type 3"};
const QStringList Constants::KEY_TONE_SOUND_ADJUSTABLE = {"Adjustable", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"};
const QStringList Constants::TIME_ZONE = {
    "GMT-12:00", "GMT-11:30", "GMT-11:00", "GMT-10:30", "GMT-10:00", "GMT-09:30", "GMT-09:00", "GMT-08:30", "GMT-08:00", "GMT-07:30", "GMT-07:00", "GMT-06:30", "GMT-06:00", "GMT-05:30", "GMT-05:00", "GMT-04:30", 
    "GMT-04:00", "GMT-03:30", "GMT-03:00", "GMT-02:30", "GMT-02:00", "GMT-01:30", "GMT-01:00", "GMT-00:30", "GMT", "GMT+00:30", "GMT+01:00", "GMT+01:30", "GMT+02:00", "GMT+02:30", "GMT+03:00", "GMT+03:30", 
    "GMT+04:00", "GMT+04:30", "GMT+05:00", "GMT+05:30", "GMT+06:00", "GMT+06:30", "GMT+07:00", "GMT+07:30", "GMT+08:00", "GMT+08:30", "GMT+09:00", "GMT+09:30", "GMT+10:00", "GMT+10:30", "GMT+11:00", "GMT+11:30", 
    "GMT+12:00", "GMT+12:30", "GMT+13:00"
};
const QStringList Constants::RANGING_INTERVAL = {
    "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", 
    "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", 
    "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", 
    "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", 
    "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", 
    "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", 
    "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", 
    "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", 
    "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148", 
    "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160", "161", "162", "163", "164", 
    "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180", 
    "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", 
    "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", 
    "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", "224", "225", "226", "227", "228", 
    "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", "242", "243", "244", 
    "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255"
};
const QStringList Constants::DISTANCE_UNIT = {"Metric", "Inch System"};
const QStringList Constants::GPS_MODE = {"GPS", "BDS", "GPS+BDS", "GLONASS", "GPS+GLON", "BDS+GLON", "ALL"};
const QStringList Constants::AUTO_REPEATER_ENABLED = {"Off", "Positive", "Negative"};
const QStringList Constants::AUTO_REPEATER_INTERVALS = {"5", "10", "15", "20", "25", "30", "35", "40", "45", "50"};
const QStringList Constants::REPEATER_OUT_OF_RANGE_NOTIFY = {"Off", "Bell", "Voice"};
const QStringList Constants::AUTO_ROAMING_START_CONDITION = {"Fixed Time", "Out Of Range"};
const QStringList Constants::ROAMING_EFFECT_WAIT_TIME = {
    "None", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", 
    "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"
};
const QStringList Constants::VFO_SCAN_TYPE = {"TO", "CO", "SE"};
const QStringList Constants::MAX_VOLUME = {"Indoors", "1", "2", "3", "4", "5", "6", "7", "8"};
const QStringList Constants::MIC_GAIN = {"1", "2", "3", "4", "5"};
const QStringList Constants::ROAMING_CHANNEL_COLOR_CODE {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "No Use"
};
const QStringList Constants::ROAMING_CHANNEL_SLOT {
    "Slot1", "Slot2", "No Use"
};
const QStringList Constants::FM_SCAN = {"Del", "Add"};
const QStringList Constants::ANALOG_EMERGENCY_ALARM = {"Alarm", "Transpond+Background", "Transpond+Alarm", "Both"};
const QStringList Constants::ANALOG_EMERGENCY_ENI_SELECT = {"None", "DTMF", "5Tone"};
const QStringList Constants::ALARM_DURATION = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", 
    "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", 
    "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", 
    "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", 
    "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", 
    "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", 
    "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", 
    "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", "128", 
    "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", "144", 
    "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", "160", 
    "161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", 
    "177", "178", "179", "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", "192", 
    "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", 
    "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", "224", 
    "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", 
    "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254"
};
const QStringList Constants::ENI_SEND_SELECT = {"Assigned Channel", "Selected Channel"};
const QStringList Constants::WORK_ALONE_VOICE_SWITCH = {
    "1m", "2m", "3m", "4m", "5m", "6m", "7m", "8m", "9m", "10m", "11m", "12m", "13m", "14m", "15m", "16m", 
    "17m", "18m", "19m", "20m", "21m", "22m", "23m", "24m", "25m", "26m", "27m", "28m", "29m", "30m", "31m", "32m", 
    "33m", "34m", "35m", "36m", "37m", "38m", "39m", "40m", "41m", "42m", "43m", "44m", "45m", "46m", "47m", "48m", 
    "49m", "50m", "51m", "52m", "53m", "54m", "55m", "56m", "57m", "58m", "59m", "60m", "61m", "62m", "63m", "64m", 
    "65m", "66m", "67m", "68m", "69m", "70m", "71m", "72m", "73m", "74m", "75m", "76m", "77m", "78m", "79m", "80m", 
    "81m", "82m", "83m", "84m", "85m", "86m", "87m", "88m", "89m", "90m", "91m", "92m", "93m", "94m", "95m", "96m", 
    "97m", "98m", "99m", "100m", "101m", "102m", "103m", "104m", "105m", "106m", "107m", "108m", "109m", "110m", "111m", "112m", 
    "113m", "114m", "115m", "116m", "117m", "118m", "119m", "120m", "121m", "122m", "123m", "124m", "125m", "126m", "127m", "128m", 
    "129m", "130m", "131m", "132m", "133m", "134m", "135m", "136m", "137m", "138m", "139m", "140m", "141m", "142m", "143m", "144m", 
    "145m", "146m", "147m", "148m", "149m", "150m", "151m", "152m", "153m", "154m", "155m", "156m", "157m", "158m", "159m", "160m", 
    "161m", "162m", "163m", "164m", "165m", "166m", "167m", "168m", "169m", "170m", "171m", "172m", "173m", "174m", "175m", "176m", 
    "177m", "178m", "179m", "180m", "181m", "182m", "183m", "184m", "185m", "186m", "187m", "188m", "189m", "190m", "191m", "192m", 
    "193m", "194m", "195m", "196m", "197m", "198m", "199m", "200m", "201m", "202m", "203m", "204m", "205m", "206m", "207m", "208m", 
    "209m", "210m", "211m", "212m", "213m", "214m", "215m", "216m", "217m", "218m", "219m", "220m", "221m", "222m", "223m", "224m", 
    "225m", "226m", "227m", "228m", "229m", "230m", "231m", "232m", "233m", "234m", "235m", "236m", "237m", "238m", "239m", "240m", 
    "241m", "242m", "243m", "244m", "245m", "246m", "247m", "248m", "249m", "250m", "251m", "252m", "253m", "254m", "255m"
};
const QStringList Constants::WORK_ALONE_AREA_SWITCH = {
    "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "11s", "12s", "13s", "14s", "15s", "16s", 
    "17s", "18s", "19s", "20s", "21s", "22s", "23s", "24s", "25s", "26s", "27s", "28s", "29s", "30s", "31s", "32s", 
    "33s", "34s", "35s", "36s", "37s", "38s", "39s", "40s", "41s", "42s", "43s", "44s", "45s", "46s", "47s", "48s", 
    "49s", "50s", "51s", "52s", "53s", "54s", "55s", "56s", "57s", "58s", "59s", "60s", "61s", "62s", "63s", "64s", 
    "65s", "66s", "67s", "68s", "69s", "70s", "71s", "72s", "73s", "74s", "75s", "76s", "77s", "78s", "79s", "80s", 
    "81s", "82s", "83s", "84s", "85s", "86s", "87s", "88s", "89s", "90s", "91s", "92s", "93s", "94s", "95s", "96s", 
    "97s", "98s", "99s", "100s", "101s", "102s", "103s", "104s", "105s", "106s", "107s", "108s", "109s", "110s", "111s", "112s", 
    "113s", "114s", "115s", "116s", "117s", "118s", "119s", "120s", "121s", "122s", "123s", "124s", "125s", "126s", "127s", "128s", 
    "129s", "130s", "131s", "132s", "133s", "134s", "135s", "136s", "137s", "138s", "139s", "140s", "141s", "142s", "143s", "144s", 
    "145s", "146s", "147s", "148s", "149s", "150s", "151s", "152s", "153s", "154s", "155s", "156s", "157s", "158s", "159s", "160s", 
    "161s", "162s", "163s", "164s", "165s", "166s", "167s", "168s", "169s", "170s", "171s", "172s", "173s", "174s", "175s", "176s", 
    "177s", "178s", "179s", "180s", "181s", "182s", "183s", "184s", "185s", "186s", "187s", "188s", "189s", "190s", "191s", "192s", 
    "193s", "194s", "195s", "196s", "197s", "198s", "199s", "200s", "201s", "202s", "203s", "204s", "205s", "206s", "207s", "208s", 
    "209s", "210s", "211s", "212s", "213s", "214s", "215s", "216s", "217s", "218s", "219s", "220s", "221s", "222s", "223s", "224s", 
    "225s", "226s", "227s", "228s", "229s", "230s", "231s", "232s", "233s", "234s", "235s", "236s", "237s", "238s", "239s", "240s", 
    "241s", "242s", "243s", "244s", "245s", "246s", "247s", "248s", "249s", "250s", "251s", "252s", "253s", "254s", "255s"
};
const QStringList Constants::WORK_ALONE_MIC_SWITCH = {"Key", "Voice Transmit"};
const QStringList Constants::DIGITAL_EMERGENCY_ALARM = {"Alarm", "Transpond+Background", "Transpond+NoLocalAlarm", "Transpond+LocalAlarm"};
const QStringList Constants::MAN_DOWN_DELAY = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", 
    "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", 
    "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", 
    "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", 
    "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", 
    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", 
    "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", 
    "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", 
    "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", 
    "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155", "156", "157", "158", "159", 
    "160", "161", "162", "163", "164", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", 
    "176", "177", "178", "179", "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191", 
    "192", "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", 
    "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", 
    "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", 
    "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254"
};
const QStringList Constants::APRS_ALT_DATA = {"Feet", "Meter"};
const QStringList Constants::DTMF_TX_TIME = {"50ms", "100ms", "200ms", "300ms", "500ms"};
const QStringList Constants::TONE_INTERVAL_CHARACTER = {"A", "B", "C", "D", "*", "#"};
const QStringList Constants::DECODING_RESPONSE = {"None", "Beep Tone", "Beep Tone & Respond"};
const QStringList Constants::DECODING_STANDARD = {
    "ZVEI1", "ZVEI2", "ZVEI3", "PZVEI", "DZVEI", "PDZVEI", "CCIR1", "CCIR2",
    "PCCIR", "EEA", "EURO SIGNAL", "NATEL", "MODAT", "CCITT", "EIA"
};
const QStringList Constants::FUNCTION_OPTION = {
    "Squelch Off", "Call All", "Emergency Alarm", "Remotely Kill",
    "Remotely Stun", "Remotely Wake Up", "Msg Group"
};
const QStringList Constants::DECODING_STANDARD_DESC = {
    "ZVEI1\nTONE FREQ(Hz)\n0 2400\n1 1060\n2 1160\n3 1270\n4 1400\n5 1530\n6 1670\n7 1830\n8 2000\n9 2200\nA 2800\nB 810\nC 970\nD 885\nE 2600\nF 680\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "ZVEI2\nTONE FREQ(Hz)\n0 2400\n1 1060\n2 1160\n3 1270\n4 1400\n5 1530\n6 1670\n7 1830\n8 2000\n9 2200\nA 885\nB 810\nC 740\nD 680\nE 970\nF 2600\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "ZVEI3\nTONE FREQ(Hz)\n0 2200\n1 970\n2 1060\n3 1160\n4 1270\n5 1400\n6 1530\n7 1670\n8 1830\n9 2000\nA 885\nB \nC \nD \nE 2400\nF \nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "PZVEI\nTONE FREQ(Hz)\n0 2400\n1 1060\n2 1160\n3 1270\n4 1400\n5 1530\n6 1670\n7 1830\n8 2000\n9 2200\nA 970\nB 810\nC 2800\nD 885\nE 2600\nF 680\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "DZVEI\nTONE FREQ(Hz)\n0 2200\n1 970\n2 1060\n3 1160\n4 1270\n5 1400\n6 1530\n7 1670\n8 1830\n9 2000\nA 825/885\nB 740\nC 2600\nD 885\nE 2400\nF 680\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "PDZVEI\nTONE FREQ(Hz)\n0 2200\n1 970\n2 1060\n3 1160\n4 1270\n5 1400\n6 1530\n7 1670\n8 1830\n9 2000\nA 825\nB 886\nC 2600\nD 856\nE 2400\nF \nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "CCIR1\nTONE FREQ(Hz)\n0 1981\n1 1124\n2 1197\n3 1275\n4 1358\n5 1446\n6 1540\n7 1640\n8 1747\n9 1860\nA 2400\nB 930\nC 2247\nD 991\nE 2110\nF 1055\nLENGTH(ms) 100\nGROUP TONE A\nREPEAT TONE E",
    "CCIR2\nTONE FREQ(Hz)\n0 1981\n1 1124\n2 1197\n3 1275\n4 1358\n5 1446\n6 1540\n7 1640\n8 1747\n9 1860\nA 2400\nB 930\nC 2247\nD 991\nE 2110\nF 1055\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "PCCIR\nTONE FREQ(Hz)\n0 1981\n1 1124\n2 1197\n3 1275\n4 1358\n5 1446\n6 1540\n7 1640\n8 1747\n9 1860\nA 1050\nB 930\nC 2400\nD 991\nE 2110\nF \nLENGTH(ms) 100\nGROUP TONE A\nREPEAT TONE E",
    "EEA\nTONE FREQ(Hz)\n0 1981\n1 1124\n2 1197\n3 1275\n4 1358\n5 1446\n6 1540\n7 1640\n8 1747\n9 1860\nA 1055\nB 930\nC 2400\nD 991\nE 2110\nF 2247\nLENGTH(ms) 40\nGROUP TONE A\nREPEAT TONE E",
    "EURO SIGNAL\nTONE FREQ(Hz)\n0 979.8\n1 903.1\n2 832.5\n3 767.4\n4 707.4\n5 652.0\n6 601.0\n7 554.0\n8 510.7\n9 470.8\nA \nB \nC \nD \nE 1062.9\nF \nLENGTH(ms) 100\nGROUP TONE A\nREPEAT TONE E",
    "NATEL\nTONE FREQ(Hz)\n0 1633\n1 631\n2 697\n3 770\n4 852\n5 941\n6 1040\n7 1209\n8 1336\n9 1477\nA 1995\nB 571\nC 2205\nD 2437\nE 1805\nF 2694\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "MODAT\nTONE FREQ(Hz)\n0 637.5\n1 787.5\n2 937.5\n3 1087.5\n4 1237.5\n5 1387.5\n6 1537.5\n7 1687.5\n8 1837.5\n9 1987.5\nA \nB \nC \nD \nE 487.5\nF \nLENGTH(ms) 40\nGROUP TONE A\nREPEAT TONE E",
    "CCITT\nTONE FREQ(Hz)\n0 400.0\n1 697.0\n2 770.0\n3 852.0\n4 941.0\n5 1209.0\n6 1335.0\n7 1477.0\n8 1663.0\n9 1800.0\nA 1900.0\nB 2000.0\nC 2100.0\nD 2200.0\nE 2300.0\nF 0.0\nLENGTH(ms) 70\nGROUP TONE A\nREPEAT TONE E",
    "EIA\nTONE FREQ(Hz)\n0 600.0\n1 741.0\n2 882.0\n3 1023.0\n4 1164.0\n5 1305.0\n6 1446.0\n7 1587.0\n8 1728.0\n9 1869.0\nA 2151.0\nB 2433.0\nC 2010.0\nD 2292.0\nE 459.0\nF 1091.0\nLENGTH(ms) 33\nGROUP TONE A\nREPEAT TONE E"

};
const QStringList Constants::RADIO_MODE_BAND = {
    "UHF{400-480 136-174 Tx:400-480 136-174", 
    "UHF{400-480 136-174 Tx:400-480 136-174 (12.5KHz Only)", 
    "UHF{430-440 136-174 Tx:430-440 136-174", 
    "UHF{400-480 136-174 Tx:430-440 144-146", 
    "UHF{434-438 144-146 Tx:434-438 144-146", 
    "UHF{434-447 144-146 Tx:434-447 144-146", 
    "UHF{446-447 136-174 Tx:446-447 136-174", 
    "UHF{400-480 136-174 Tx:420-450 144-148", 
    "UHF{400-470 136-174 Tx:400-470 136-174", 
    "UHF{430-432 144-146 Tx:430-432 144-146", 
    "UHF{400-480 136-174 Tx:430-450 144-148", 
    "UHF{400-520 136-174 Tx:400-520 136-174", 
    "UHF{400-490 136-174 Tx:400-490 136-174", 
    "UHF{400-480 136-174 Tx:403-470 136-174", 
    "UHF{400-520 220-225 136-174 Tx:400-520 220-225 136-174", 
    "UHF{420-520 144-148 Tx:420-520 144-148", 
    "UHF{430-440 144-147 Tx:430-440 144-147", 
    "UHF{430-440 136-174 Tx:136-174", 
    "UHF{400-480 220-225 136-174 Tx:420-450 222-225 144-148"
};

const QStringList Constants::TALKALIAS_DISPLAY_PRIORITY_878 = {"Off", "Contact Alias", "Air Alias"};
const QStringList Constants::TALKALIAS_DISPLAY_PRIORITY_890 = {"Off", "Contact Alias", "Air Alias DMR/NX"};
const QStringList Constants::TALKALIAS_DATA_FORMAT = {"ISO 8", "IOS 7", "Unicode"};
const QStringList Constants::HOTKEY_MENU = {
    "Off", "SMS", "New SMS", "Hot Text", "Received SMS", "Send SMS", "Contact List", "Manual Dial",
    "Call Log", "Dialed Call", "Received Call", "Missed Call", "Zone", "Radio Set", "Channel Set"
};
const QStringList Constants::SCRAMBLER = {
    "Off", "3.5k", "3.39k", "3.3k", "3.29k", "3.2k", "3.1k", "3.0k", "2.9k",
    "2.8k", "2.7k", "2.6k", "2.5k", "4.095k", "3.458k"
};
const QStringList Constants::CUSTOM_SCRAMBLER = {
    "1.3k", "1.4k", "1.5k", "1.6k", "1.7k", "1.8k", "1.9k", "2.1k", "2.2k", "2.3k",
    "2.4k", "2.5k", "2.6k", "2.7k", "2.8k", "2.9k", "3k", "3.1k", "3.2k", "3.3k",
    "3.4k", "3.5k", "3.6k", "3.7k", "3.8k", "3.9k", "4k", "4.1k"
};