function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "aurix_mbd_test"};
	this.sidHashMap["aurix_mbd_test"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "aurix_mbd_test:3"};
	this.sidHashMap["aurix_mbd_test:3"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S2>"] = {sid: "aurix_mbd_test:7"};
	this.sidHashMap["aurix_mbd_test:7"] = {rtwname: "<S2>"};
	this.rtwnameHashMap["<Root>/Core Initialise"] = {sid: "aurix_mbd_test:1"};
	this.sidHashMap["aurix_mbd_test:1"] = {rtwname: "<Root>/Core Initialise"};
	this.rtwnameHashMap["<Root>/Core Run Fcn"] = {sid: "aurix_mbd_test:2"};
	this.sidHashMap["aurix_mbd_test:2"] = {rtwname: "<Root>/Core Run Fcn"};
	this.rtwnameHashMap["<Root>/Core0_Init"] = {sid: "aurix_mbd_test:3"};
	this.sidHashMap["aurix_mbd_test:3"] = {rtwname: "<Root>/Core0_Init"};
	this.rtwnameHashMap["<Root>/Core0_run"] = {sid: "aurix_mbd_test:7"};
	this.sidHashMap["aurix_mbd_test:7"] = {rtwname: "<Root>/Core0_run"};
	this.rtwnameHashMap["<S1>/function"] = {sid: "aurix_mbd_test:5"};
	this.sidHashMap["aurix_mbd_test:5"] = {rtwname: "<S1>/function"};
	this.rtwnameHashMap["<S1>/Config IO"] = {sid: "aurix_mbd_test:11"};
	this.sidHashMap["aurix_mbd_test:11"] = {rtwname: "<S1>/Config IO"};
	this.rtwnameHashMap["<S1>/SerialConfig"] = {sid: "aurix_mbd_test:33"};
	this.sidHashMap["aurix_mbd_test:33"] = {rtwname: "<S1>/SerialConfig"};
	this.rtwnameHashMap["<S2>/function"] = {sid: "aurix_mbd_test:9"};
	this.sidHashMap["aurix_mbd_test:9"] = {rtwname: "<S2>/function"};
	this.rtwnameHashMap["<S2>/Add"] = {sid: "aurix_mbd_test:28"};
	this.sidHashMap["aurix_mbd_test:28"] = {rtwname: "<S2>/Add"};
	this.rtwnameHashMap["<S2>/Chart"] = {sid: "aurix_mbd_test:38"};
	this.sidHashMap["aurix_mbd_test:38"] = {rtwname: "<S2>/Chart"};
	this.rtwnameHashMap["<S2>/Constant"] = {sid: "aurix_mbd_test:27"};
	this.sidHashMap["aurix_mbd_test:27"] = {rtwname: "<S2>/Constant"};
	this.rtwnameHashMap["<S2>/Constant1"] = {sid: "aurix_mbd_test:31"};
	this.sidHashMap["aurix_mbd_test:31"] = {rtwname: "<S2>/Constant1"};
	this.rtwnameHashMap["<S2>/Data Type Conversion"] = {sid: "aurix_mbd_test:39"};
	this.sidHashMap["aurix_mbd_test:39"] = {rtwname: "<S2>/Data Type Conversion"};
	this.rtwnameHashMap["<S2>/DigitalWrite"] = {sid: "aurix_mbd_test:34"};
	this.sidHashMap["aurix_mbd_test:34"] = {rtwname: "<S2>/DigitalWrite"};
	this.rtwnameHashMap["<S2>/Divide"] = {sid: "aurix_mbd_test:30"};
	this.sidHashMap["aurix_mbd_test:30"] = {rtwname: "<S2>/Divide"};
	this.rtwnameHashMap["<S2>/Memory"] = {sid: "aurix_mbd_test:29"};
	this.sidHashMap["aurix_mbd_test:29"] = {rtwname: "<S2>/Memory"};
	this.rtwnameHashMap["<S2>/Pulse Generator"] = {sid: "aurix_mbd_test:40"};
	this.sidHashMap["aurix_mbd_test:40"] = {rtwname: "<S2>/Pulse Generator"};
	this.rtwnameHashMap["<S2>/Scope"] = {sid: "aurix_mbd_test:41"};
	this.sidHashMap["aurix_mbd_test:41"] = {rtwname: "<S2>/Scope"};
	this.rtwnameHashMap["<S2>/SerialSendString"] = {sid: "aurix_mbd_test:25"};
	this.sidHashMap["aurix_mbd_test:25"] = {rtwname: "<S2>/SerialSendString"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();