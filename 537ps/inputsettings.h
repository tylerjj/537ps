//Author: Tyler Johnston
#ifndef INPUTSETTINGS
#define INPUTSETTINGS


typedef struct {
	//TODO Does each member need a comment describing its purpose?
	int flag_p;
        int flag_s;
        int flag_U;
        int flag_S;
        int flag_v;
        int flag_c;
        // I'm aware that this list should probably be its own struct.
        // I'm avoiding this due to my lack of familiarity with C.
        int max_length;
        int pid_count;
        long list_pid[];
} InputSettings;

InputSettings* initInputSettings(int argc);

int addPIDInputSettings(InputSettings* inset_ptr, long pid);

int freeInputSettings(InputSettings* inset_ptr);

#endif
