

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0595 */
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IWdsTransportCacheable,0x46AD894B,0x0BAB,0x47DC,0x84,0xB2,0x7B,0x55,0x3F,0x1D,0x8F,0x80);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportCollection,0xB8BA4B1A,0x2FF4,0x43AB,0x99,0x6C,0xB2,0xB1,0x0A,0x91,0xA6,0xEB);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportManager,0x5B0D35F5,0x1B13,0x4AFD,0xB8,0x78,0x65,0x26,0xDC,0x34,0x0B,0x5D);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportServer,0x09CCD093,0x830D,0x4344,0xA3,0x0A,0x73,0xAE,0x8E,0x8F,0xCA,0x90);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportServer2,0x256e999f,0x6df4,0x4538,0x81,0xb9,0x85,0x7b,0x9a,0xb8,0xfb,0x47);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportSetupManager,0xF7238425,0xEFA8,0x40A4,0xAE,0xF9,0xC9,0x8D,0x96,0x9C,0x0B,0x75);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportSetupManager2,0x02BE79DA,0x7E9E,0x4366,0x8B,0x6E,0x2A,0xA9,0xA9,0x1B,0xE4,0x7F);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportConfigurationManager,0x84CC4779,0x42DD,0x4792,0x89,0x1E,0x13,0x21,0xD6,0xD7,0x4B,0x44);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportConfigurationManager2,0xD0D85CAF,0xA153,0x4F1D,0xA9,0xDD,0x96,0xF4,0x31,0xC5,0x07,0x17);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportNamespaceManager,0x3E22D9F6,0x3777,0x4D98,0x83,0xE1,0xF9,0x86,0x96,0x71,0x7B,0xA3);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportTftpManager,0x1327a7c8,0xae8a,0x4fb3,0x81,0x50,0x13,0x62,0x27,0xc3,0x7e,0x9a);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportServicePolicy,0xB9468578,0x9F2B,0x48CC,0xB2,0x7A,0xA6,0x07,0x99,0xC2,0x75,0x0C);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportServicePolicy2,0x65C19E5C,0xAA7E,0x4B91,0x89,0x44,0x91,0xE0,0xE5,0x57,0x27,0x97);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportDiagnosticsPolicy,0x13B33EFC,0x7856,0x4F61,0x9A,0x59,0x8D,0xE6,0x7B,0x6B,0x87,0xB6);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportMulticastSessionPolicy,0x4E5753CF,0x68EC,0x4504,0xA9,0x51,0x4A,0x00,0x32,0x66,0x60,0x6B);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportNamespace,0xFA561F57,0xFBEF,0x4ED3,0xB0,0x56,0x12,0x7C,0xB1,0xB3,0x3B,0x84);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportNamespaceAutoCast,0xAD931A72,0xC4BD,0x4C41,0x8F,0xBC,0x59,0xC9,0xC7,0x48,0xDF,0x9E);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportNamespaceScheduledCast,0x3840CECF,0xD76C,0x416E,0xA4,0xCC,0x31,0xC7,0x41,0xD2,0x87,0x4B);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportNamespaceScheduledCastManualStart,0x013E6E4C,0xE6A7,0x4FB5,0xB7,0xFF,0xD9,0xF5,0xDA,0x80,0x5C,0x31);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportNamespaceScheduledCastAutoStart,0xD606AF3D,0xEA9C,0x4219,0x96,0x1E,0x74,0x91,0xD6,0x18,0xD9,0xB9);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportContent,0xD405D711,0x0296,0x4AB4,0xA8,0x60,0xAC,0x7D,0x32,0xE6,0x57,0x98);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportSession,0xF4EFEA88,0x65B1,0x4F30,0xA4,0xB9,0x27,0x93,0x98,0x77,0x96,0xFB);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportClient,0xB5DBC93A,0xCABE,0x46CA,0x83,0x7F,0x3E,0x44,0xE9,0x3C,0x65,0x45);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportTftpClient,0xb022d3ae,0x884d,0x4d85,0xb1,0x46,0x53,0x32,0x0e,0x76,0xef,0x62);


MIDL_DEFINE_GUID(IID, IID_IWdsTransportContentProvider,0xB9489F24,0xF219,0x4ACF,0xAA,0xD7,0x26,0x5C,0x7C,0x08,0xA6,0xAE);


MIDL_DEFINE_GUID(IID, LIBID_WdsTptMgmtLib,0x9212887F,0xF5BC,0x45DD,0xA5,0x10,0x26,0x54,0x13,0xA1,0x8E,0xD7);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportCacheable,0x70590B16,0xF146,0x46BD,0xBD,0x9D,0x4A,0xAA,0x90,0x08,0x4B,0xF5);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportCollection,0xC7F18B09,0x391E,0x436E,0xB1,0x0B,0xC3,0xEF,0x46,0xF2,0xC3,0x4F);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportManager,0xF21523F6,0x837C,0x4A58,0xAF,0x99,0x8A,0x7E,0x27,0xF8,0xFF,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportServer,0xEA19B643,0x4ADF,0x4413,0x94,0x2C,0x14,0xF3,0x79,0x11,0x87,0x60);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportSetupManager,0xC7BEEAAD,0x9F04,0x4923,0x9F,0x0C,0xFB,0xF5,0x2B,0xC7,0x59,0x0F);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportConfigurationManager,0x8743F674,0x904C,0x47CA,0x85,0x12,0x35,0xFE,0x98,0xF6,0xB0,0xAC);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportNamespaceManager,0xF08CDB63,0x85DE,0x4A28,0xA1,0xA9,0x5C,0xA3,0xE7,0xEF,0xDA,0x73);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportServicePolicy,0x65ACEADC,0x2F0B,0x4F43,0x9F,0x4D,0x81,0x18,0x65,0xD8,0xCE,0xAD);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportDiagnosticsPolicy,0xEB3333E1,0xA7AD,0x46F5,0x80,0xD6,0x6B,0x74,0x02,0x04,0xE5,0x09);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportMulticastSessionPolicy,0x3C6BC3F4,0x6418,0x472A,0xB6,0xF1,0x52,0xD4,0x57,0x19,0x54,0x37);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportNamespace,0xD8385768,0x0732,0x4EC1,0x95,0xEA,0x16,0xDA,0x58,0x19,0x08,0xA1);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportNamespaceAutoCast,0xB091F5A8,0x6A99,0x478D,0xB2,0x3B,0x09,0xE8,0xFE,0xE0,0x45,0x74);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportNamespaceScheduledCast,0xBADC1897,0x7025,0x44EB,0x91,0x08,0xFB,0x61,0xC4,0x05,0x57,0x92);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportNamespaceScheduledCastManualStart,0xD3E1A2AA,0xCAAC,0x460E,0xB9,0x8A,0x47,0xF9,0xF3,0x18,0xA1,0xFA);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportNamespaceScheduledCastAutoStart,0xA1107052,0x122C,0x4B81,0x9B,0x7C,0x38,0x6E,0x68,0x55,0x38,0x3F);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportContent,0x0A891FE7,0x4A3F,0x4C65,0xB6,0xF2,0x14,0x67,0x61,0x96,0x79,0xEA);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportSession,0x749AC4E0,0x67BC,0x4743,0xBF,0xE5,0xCA,0xCB,0x1F,0x26,0xF5,0x7F);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportClient,0x66D2C5E9,0x0FF6,0x49EC,0x97,0x33,0xDA,0xFB,0x1E,0x01,0xDF,0x1C);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportTftpClient,0x50343925,0x7c5c,0x4c8c,0x96,0xc4,0xad,0x9f,0xa5,0x00,0x5f,0xba);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportTftpManager,0xc8e9dca2,0x3241,0x4e4d,0xb8,0x06,0xbc,0x74,0x01,0x9d,0xfe,0xda);


MIDL_DEFINE_GUID(CLSID, CLSID_WdsTransportContentProvider,0xE0BE741F,0x5A75,0x4EB9,0x8A,0x2D,0x5E,0x18,0x9B,0x45,0xF3,0x27);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



