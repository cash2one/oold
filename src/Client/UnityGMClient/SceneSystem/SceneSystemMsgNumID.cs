﻿using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    class CSceneSystemMsgNumID
    {
        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_SCENE = 1;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_SCENE = 2;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_QUIT_SCENE = 3;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_QUIT_SCENE = 4;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLE_REVIVE = 5;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLE_REVIVE = 6;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_ROLE_ARENA_DATA = 7;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_ROLE_ARENA_DATA = 8;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_NEW_ARENA_CHALLENGEES = 9;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_NEW_ARENA_CHALLENGEES = 10;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CHALLENGE_ARENA_ROLE = 11;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CHALLENGE_ARENA_ROLE = 12;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CHALLENGE_ARENA_ROLE_FINISH = 13;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CHALLENGE_ARENA_ROLE_FINISH = 14;

        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ADD_NEW_ARENA_CHALLENGE_RECORD = 16;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_STORY_INSTANCE_PROGRESS = 17;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_STORY_INSTANCE_PROGRESS = 18;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_DATA = 19;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_DATA = 20;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_STAGE = 21;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_STAGE = 22;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_STAGE_REPORT_RESULT = 23;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_STAGE_REPORT_RESULT = 24;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_CLEAR_STAGE = 25;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_CLEAR_STAGE = 26;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_STAR_PRIZE = 27;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_STAR_PRIZE = 28;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_INSTANCE_STAR_PRIZE_PROGRESS = 29;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_INSTANCE_STAR_PRIZE_PROGRESS = 30;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_CONTINUOUS_INSTANCE_DATA = 31;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_CONTINUOUS_INSTANCE_DATA = 32;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_CONTINUOUS_STAGE = 33;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_CONTINUOUS_STAGE = 34;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_REPORT_CONTINUOUS_STAGE_RESULT = 35;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_REPORT_CONTINUOUS_STAGE_RESULT = 36;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLL_FAST_CLEAR_CONTINUOUS_STAGE_NUM = 37;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLL_FAST_CLEAR_CONTINUOUS_STAGE_NUM = 38;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_RESET_CONTINUOUS_INSTANCE_DATA = 39;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_RESET_CONTINUOUS_INSTANCE_DATA = 40;

        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_NTF_ROLE_ENTER_SCENE = 41;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_NTF_ROLE_EXIT_SCENE = 42;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ROLE_MOVE = 43;
	    public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ROLE_MOVE = 44;
	    public const uint EMSGNUMID_SCENESYSTEM_GM2GC_NTF_ROLE_MOVE = 45;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_DETERMINE_STAGE_PRIZE_ITEM = 47;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_DETERMINE_STAGE_PRIZE_ITEM = 48;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_ENTER_RANDOM_STAGE = 49;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_ENTER_RANDOM_STAGE = 50;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_SEND_RANDOM_STAGE_RESULT = 51;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_SEND_RANDOM_STAGE_RESULT = 52;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_GET_GREED_LAND_INFO = 53;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_GET_GREED_LAND_INFO = 54;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_PURCHASE_ARENA_TICKETS = 55;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_PURCHASE_ARENA_TICKETS = 56;

        public const uint EMSGNUMID_SCENESYSTEM_GC2GM_REQ_RESTORE_STAGE_TICKET = 57;
        public const uint EMSGNUMID_SCENESYSTEM_GM2GC_ACK_RESTORE_STAGE_TICKETS = 58;



    }



}


