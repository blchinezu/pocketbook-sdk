#ifndef PBUTILITIES_H
#define PBUTILITIES_H

#include "pbrect.h"
#include "inkview.h"
#include <sys/timeb.h>
#include <stdint.h>

void MakeInvert(std::vector<PBRect> &rectList);
void MakeInvert(PBRect &rect);
double getCurrentTime();
void _start_time_trace();
void _trace_time(const char * message);
int isRegistered();

#endif // PBUTILITIES_H
