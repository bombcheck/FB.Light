#pragma once

#include "fastpin_esp8266.h"

#ifdef FASTLED_ESP8266_DMA
#include "clockless_esp8266_dma.h"
#else
#include "clockless_esp8266.h"
#endif
#include "clockless_block_esp8266.h"
