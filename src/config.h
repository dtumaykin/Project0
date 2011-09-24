#ifndef P0_CONFIG_H
#define P0_CONFIG_H

int loadConfig(char * path, scene_t &scene); //return 0 in case of bad config

scene_t config(); // loads default "config.cfg" file and returns a scene, implemented by secco92


#endif
