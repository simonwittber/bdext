
#if _WINDOWS
#define DLLExport extern "C" __declspec(dllexport)
#endif
#if MAC
#define DLLExport extern "C"
#endif

#include "../common/BiduleSDK.h"
#include "TriggerSelector.h"
#include "TriggerSelector16.h"
#include "RandRange.h"
#include "RandWalk.h"
#include "FlipFlop.h"
#include "Valve.h"
#include "Stepper.h"
#include "TriggerPattern.h"
#include "Progress.h"
#include "Latch.h"

using namespace plogue::biduleSDK;
using namespace acme;

DLLExport unsigned long getNumBidules()
{
    return 11;
}

DLLExport ErrorCode fillBiduleInfo(unsigned long biduleIdx, BidulePluginInfo *biduleInfo)
{
    //return NO_PLUGIN if no plugin for that idx
    //return NO_ERROR for OK
    //shouldn't happen but there's nothing
    //wrong with some error handling mechanisms
    switch (biduleIdx)
    {
    case 0:
        strcpy(biduleInfo->type, "com.acme.RandRange");
        strcpy(biduleInfo->name, "RandRange");
        strcpy(biduleInfo->fullName, "SRW\tRandRange");
        return BSDK_NO_ERROR;
        break;
    case 1:
        strcpy(biduleInfo->type, "com.acme.FlipFlop");
        strcpy(biduleInfo->name, "FlipFlop");
        strcpy(biduleInfo->fullName, "SRW\tFlipFlop");
        return BSDK_NO_ERROR;
        break;
    case 2:
        strcpy(biduleInfo->type, "com.acme.Valve");
        strcpy(biduleInfo->name, "Valve");
        strcpy(biduleInfo->fullName, "SRW\tValve");
        return BSDK_NO_ERROR;
        break;
    case 3:
        strcpy(biduleInfo->type, "com.acme.RandWalk");
        strcpy(biduleInfo->name, "RandWalk");
        strcpy(biduleInfo->fullName, "SRW\tRandWalk");
        return BSDK_NO_ERROR;
        break;
    case 4:
        strcpy(biduleInfo->type, "com.acme.TriggerSelector");
        strcpy(biduleInfo->name, "TriggerSelector");
        strcpy(biduleInfo->fullName, "SRW\tTriggerSelector");
        return BSDK_NO_ERROR;
        break;
    case 5:
        strcpy(biduleInfo->type, "com.acme.TriggerSelector16");
        strcpy(biduleInfo->name, "TriggerSelector16");
        strcpy(biduleInfo->fullName, "SRW\tTriggerSelector16");
        return BSDK_NO_ERROR;
        break;
    case 6:
        strcpy(biduleInfo->type, "com.acme.Stepper");
        strcpy(biduleInfo->name, "Stepper");
        strcpy(biduleInfo->fullName, "SRW\tStepper");
        return BSDK_NO_ERROR;
        break;
    case 7:
        strcpy(biduleInfo->type, "com.acme.TriggerPattern");
        strcpy(biduleInfo->name, "TriggerPattern");
        strcpy(biduleInfo->fullName, "SRW\tTriggerPattern");
        return BSDK_NO_ERROR;
        break;
    case 8:
        strcpy(biduleInfo->type, "com.acme.RandomTriggerGate");
        strcpy(biduleInfo->name, "RandomTriggerGate");
        strcpy(biduleInfo->fullName, "SRW\tRandomTriggerGate");
        return BSDK_NO_ERROR;
        break;
    case 9:
        strcpy(biduleInfo->type, "com.acme.Progress");
        strcpy(biduleInfo->name, "Progress");
        strcpy(biduleInfo->fullName, "SRW\tProgress");
        return BSDK_NO_ERROR;
        break;
    case 10:
        strcpy(biduleInfo->type, "com.acme.Latch");
        strcpy(biduleInfo->name, "Latch");
        strcpy(biduleInfo->fullName, "SRW\tLatch");
        return BSDK_NO_ERROR;
        break;
    default:
        return BSDK_NO_PLUGIN;
        break;
    }
}

DLLExport BidulePluginStruct *newInstance(const char *type, BiduleHost *host)
{

    if (strcmp(type, "com.acme.RandRange") == 0)
    {
        BidulePlugin *bp = new RandRange(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.FlipFlop") == 0)
    {
        BidulePlugin *bp = new FlipFlop(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.Valve") == 0)
    {
        BidulePlugin *bp = new Valve(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.RandWalk") == 0)
    {
        BidulePlugin *bp = new RandWalk(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.TriggerSelector") == 0)
    {
        BidulePlugin *bp = new TriggerSelector(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.TriggerSelector16") == 0)
    {
        BidulePlugin *bp = new TriggerSelector16(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.Stepper") == 0)
    {
        BidulePlugin *bp = new Stepper(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.TriggerPattern") == 0)
    {
        BidulePlugin *bp = new TriggerPattern(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.Progress") == 0)
    {
        BidulePlugin *bp = new Progress(host);
        return bp->getBidulePluginStruct();
    }

    if (strcmp(type, "com.acme.Latch") == 0)
    {
        BidulePlugin *bp = new Latch(host);
        return bp->getBidulePluginStruct();
    }

    return NULL;
}

DLLExport void deleteInstance(BidulePluginStruct *ptr)
{
    if (ptr && ptr->plugin_object)
    {
        BidulePlugin *bp = (BidulePlugin *)(ptr->plugin_object);
        delete bp;
    }
}
