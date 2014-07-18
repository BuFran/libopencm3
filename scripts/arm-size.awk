BEGIN {
	STR = "   [%-6s] %6d bytes (%3.2f %% full) %s\n";
	ROM_MATCH = "^"ROM_OFF"$";
	RAM_MATCH = "^"RAM_OFF"$";
	CCM_MATCH = "^"CCM_OFF"$";
	EEP_MATCH = "^"EEP_OFF"$";
	
	ROM_USED = 0;
	RAM_USED = 0;
	CCM_USED = 0;
	EEP_USED = 0;
}
function percent(a,b) { return strtonum(a) * 100 / (strtonum(b) * 1024); }
($1 ~ /^LOAD$/ && $3 ~ ROM_MATCH) { 
	ROM_USED += strtonum($6);
}
($1 ~ /^LOAD$/ && $3 ~ RAM_MATCH) {
	RAM_USED += strtonum($6);
	ROM_USED += strtonum($6);
}
($1 ~ /^LOAD$/ && $3 ~ CCM_MATCH) { 
	CCM_USED += strtonum($6);
}
($1 ~ /^LOAD$/ && $3 ~ EEP_MATCH) {
	EEP_USED += strtonum($6);
}
# hack: section not found in previous patterns is treated as uninitialized memory residing in ram 
($1 ~ /^LOAD$/ && !($3 ~ ROM_MATCH || $3 ~ RAM_MATCH || $3 ~ CCM_MATCH || $3 ~ EEP_MATCH)) {
	RAM_USED += strtonum($6);
}
END {
	if (ROM_USED > 0) { printf STR, "FLASH",  ROM_USED, percent(ROM_USED, ROM), "[.text + .data]"; }
	if (RAM_USED > 0) { printf STR, "RAM",    RAM_USED, percent(RAM_USED, RAM), "[.data + .bss]"; }
	if (CCM_USED > 0) { printf STR, "CCM",    CCM_USED, percent(CCM_USED, CCM), "[.ccmram]"; }
	if (EEP_USED > 0) { printf STR, "EEPROM", EEP_USED, percent(EEP_USED,EEP), "[.eeprom]"; }
}

