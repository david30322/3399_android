#include <ebase/types.h>
#include <ebase/trace.h>
#include <ebase/builtins.h>

#include <common/return_codes.h>

#include "isi.h"
#include "isi_iss.h"
#include "isi_priv.h"
#include "OV5645_priv.h"


/*****************************************************************************
 * DEFINES
 *****************************************************************************/


/*****************************************************************************
 * GLOBALS
 *****************************************************************************/

// Image sensor register settings default values taken from data sheet OV8810_DS_1.1_SiliconImage.pdf.
// The settings may be altered by the code in IsiSetupSensor.
const IsiRegDescription_t OV5645_g_aRegDescription[] =
{
	{0x4202, 0x03,"0100",eReadWrite},
	{0x3103, 0x11,"0100",eReadWrite},
	{0x3008, 0x82,"0100",eReadWrite},
	{0x0 ,0x10,"0x0100",eDelay},//delay 5ms
	{0x3031, 0x00,"0100",eReadWrite},
  {0x302c, 0x42,"0100",eReadWrite},
	{0x3008, 0x42,"0100",eReadWrite},
  {0x3103, 0x03,"0100",eReadWrite},
  {0x4050, 0x6e,"0100",eReadWrite},
  {0x4051, 0x8f,"0100",eReadWrite},
  {0x5780, 0xfc,"0100",eReadWrite},
  {0x5781, 0x13,"0100",eReadWrite}, 
  {0x5782, 0x03,"0100",eReadWrite},
  {0x5786, 0x20,"0100",eReadWrite},
  {0x5787, 0x40,"0100",eReadWrite},
  {0x5788, 0x08,"0100",eReadWrite},
  {0x5789, 0x08,"0100",eReadWrite},
  {0x578a, 0x02,"0100",eReadWrite},
  {0x578b, 0x01,"0100",eReadWrite},
  {0x578c, 0x01,"0100",eReadWrite},
  {0x578d, 0x0c,"0100",eReadWrite},
  {0x578e, 0x02,"0100",eReadWrite},
  {0x578f, 0x01,"0100",eReadWrite},  
  {0x3017, 0x40,"0100",eReadWrite},
  {0x3018, 0x00,"0100",eReadWrite},
  {0x3503, 0x07,"0100",eReadWrite},
  {0x3500, 0x00,"0100",eReadWrite}, 
  {0x3501, 0x3d,"0100",eReadWrite},
  {0x3502, 0x80,"0100",eReadWrite},
  {0x350a, 0x00,"0100",eReadWrite},
  {0x350b, 0x3c,"0100",eReadWrite},
  {0x3611, 0x06,"0100",eReadWrite},
  {0x3614, 0x50,"0100",eReadWrite},
  {0x3702, 0x6e,"0100",eReadWrite},
  {0x370f, 0x10,"0100",eReadWrite},
  {0x3739, 0x70,"0100",eReadWrite},
  {0x3719, 0x86,"0100",eReadWrite},
  {0x3826, 0x03,"0100",eReadWrite},
  {0x3828, 0x08,"0100",eReadWrite},
  {0x4520, 0xb0,"0100",eReadWrite},
  {0x4818, 0x01,"0100",eReadWrite},
  {0x481d, 0xf0,"0100",eReadWrite},
  {0x481f, 0x50,"0100",eReadWrite},
  {0x4823, 0x70,"0100",eReadWrite},
  {0x4831, 0x14,"0100",eReadWrite},
  {0x505c, 0x30,"0100",eReadWrite},
  {0x5a00, 0x08,"0100",eReadWrite},
  {0x5a21, 0x00,"0100",eReadWrite},
  {0x5a24, 0x00,"0100",eReadWrite},
  {0x3108, 0x01,"0100",eReadWrite},
  {0x3630, 0x2d,"0100",eReadWrite},
  {0x3631, 0x00,"0100",eReadWrite},
  {0x3632, 0x32,"0100",eReadWrite},
  {0x3633, 0x52,"0100",eReadWrite},
  {0x3621, 0xe0,"0100",eReadWrite},
  {0x3704, 0xa0,"0100",eReadWrite},
  {0x3703, 0x52,"0100",eReadWrite},
  {0x3715, 0x08,"0100",eReadWrite},
  {0x3717, 0x01,"0100",eReadWrite},
  {0x370b, 0x61,"0100",eReadWrite},
  {0x3705, 0x33,"0100",eReadWrite},
  {0x3905, 0x02,"0100",eReadWrite},
  {0x3906, 0x10,"0100",eReadWrite},
  {0x3901, 0x0a,"0100",eReadWrite},
  {0x3731, 0x22,"0100",eReadWrite},
  {0x3600, 0x09,"0100",eReadWrite},
  {0x3601, 0x43,"0100",eReadWrite},
  {0x3620, 0x33,"0100",eReadWrite},
  {0x371b, 0x20,"0100",eReadWrite},
  {0x3a18, 0x00,"0100",eReadWrite},
  {0x3a19, 0x78,"0100",eReadWrite},
  {0x3635, 0x13,"0100",eReadWrite},
  {0x3636, 0x03,"0100",eReadWrite},
  {0x3634, 0x70,"0100",eReadWrite},
  {0x3622, 0x01,"0100",eReadWrite},
  {0x3c04, 0x28,"0100",eReadWrite},
  {0x3c05, 0x98,"0100",eReadWrite},
  {0x3c07, 0x07,"0100",eReadWrite},
  {0x3c09, 0xc2,"0100",eReadWrite},
  {0x3c0a, 0x9c,"0100",eReadWrite},
  {0x3c0b, 0x40,"0100",eReadWrite},
  {0x3004, 0xef,"0100",eReadWrite},
  {0x3820, 0x41,"0100",eReadWrite},//47
  {0x3821, 0x07,"0100",eReadWrite},//01
  {0x4514, 0x00,"0100",eReadWrite},
  {0x3800, 0x00,"0100",eReadWrite},
  {0x3801, 0x00,"0100",eReadWrite},
  {0x3802, 0x00,"0100",eReadWrite},
  {0x3803, 0x06,"0100",eReadWrite},
  {0x3804, 0x0a,"0100",eReadWrite},
  {0x3805, 0x3f,"0100",eReadWrite},
  {0x3806, 0x07,"0100",eReadWrite},
  {0x3807, 0x9d,"0100",eReadWrite},
  {0x3808, 0x05,"0100",eReadWrite},
  {0x3809, 0x00,"0100",eReadWrite},
  {0x380a, 0x03,"0100",eReadWrite},
  {0x380b, 0xc0,"0100",eReadWrite},
  {0x3810, 0x00,"0100",eReadWrite},
  {0x3811, 0x10,"0100",eReadWrite},
  {0x3812, 0x00,"0100",eReadWrite},
  {0x3813, 0x06,"0100",eReadWrite},
  {0x3814, 0x31,"0100",eReadWrite},
  {0x3815, 0x31,"0100",eReadWrite},
  {0x3034, 0x18,"0100",eReadWrite},
  {0x3035, 0x11,"0100",eReadWrite},
  {0x3036, 0x38,"0100",eReadWrite},
  {0x3037, 0x13,"0100",eReadWrite},
  {0x380c, 0x07,"0100",eReadWrite},
  {0x380d, 0x68,"0100",eReadWrite},
  {0x380e, 0x07,"0100",eReadWrite},
  {0x380f, 0xd8,"0100",eReadWrite},
  {0x3c01, 0xb4,"0100",eReadWrite},
  {0x3c00, 0x04,"0100",eReadWrite},
  {0x3a08, 0x01,"0100",eReadWrite},
  {0x3a09, 0x27,"0100",eReadWrite},
  {0x3a0e, 0x03,"0100",eReadWrite},
  {0x3a0a, 0x00,"0100",eReadWrite},
  {0x3a0b, 0xf6,"0100",eReadWrite},
  {0x3a0d, 0x04,"0100",eReadWrite},
  {0x3a00, 0x3c,"0100",eReadWrite},
  {0x3a02, 0x09,"0100",eReadWrite},
  {0x3a03, 0x3a,"0100",eReadWrite},
  {0x3a14, 0x09,"0100",eReadWrite},
  {0x3a15, 0x3a,"0100",eReadWrite},
  {0x3618, 0x00,"0100",eReadWrite},
  {0x3612, 0xab,"0100",eReadWrite},
  {0x3708, 0x66,"0100",eReadWrite},
  {0x3709, 0x52,"0100",eReadWrite},
  {0x370c, 0xc3,"0100",eReadWrite},
  {0x4001, 0x02,"0100",eReadWrite},
  {0x4004, 0x02,"0100",eReadWrite},
  {0x3002, 0x1c,"0100",eReadWrite},
  {0x3006, 0xc3,"0100",eReadWrite},
  {0x300e, 0x45,"0100",eReadWrite},
  {0x302e, 0x0b,"0100",eReadWrite},
  {0x4300, 0x30,"0100",eReadWrite},
  {0x501f, 0x00,"0100",eReadWrite},
  {0x460b, 0x37,"0100",eReadWrite},
  {0x460c, 0x20,"0100",eReadWrite},
  {0x4837, 0x11,"0100",eReadWrite},
  {0x3824, 0x01,"0100",eReadWrite},
  {0x5001, 0xa3,"0100",eReadWrite},
  {0x5180, 0xff,"0100",eReadWrite},
  {0x5181, 0xf2,"0100",eReadWrite},
  {0x5182, 0x00,"0100",eReadWrite},
  {0x5183, 0x14,"0100",eReadWrite},
  {0x5184, 0x25,"0100",eReadWrite},
  {0x5185, 0x24,"0100",eReadWrite},
  {0x5186, 0x16,"0100",eReadWrite},
  {0x5187, 0x16,"0100",eReadWrite},
  {0x5188, 0x16,"0100",eReadWrite},
  {0x5189, 0x64,"0100",eReadWrite},
  {0x518a, 0x64,"0100",eReadWrite},
  {0x518b, 0xe0,"0100",eReadWrite},
  {0x518c, 0xb2,"0100",eReadWrite},
  {0x518d, 0x42,"0100",eReadWrite},
  {0x518e, 0x30,"0100",eReadWrite},
  {0x518f, 0x4c,"0100",eReadWrite},
  {0x5190, 0x56,"0100",eReadWrite},
  {0x5191, 0xf8,"0100",eReadWrite},
  {0x5192, 0x04,"0100",eReadWrite},
  {0x5193, 0x70,"0100",eReadWrite},
  {0x5194, 0xf0,"0100",eReadWrite},
  {0x5195, 0xf0,"0100",eReadWrite},
  {0x5196, 0x03,"0100",eReadWrite},
  {0x5197, 0x01,"0100",eReadWrite},
  {0x5198, 0x04,"0100",eReadWrite},
  {0x5199, 0x12,"0100",eReadWrite},
  {0x519a, 0x04,"0100",eReadWrite},
  {0x519b, 0x00,"0100",eReadWrite},
  {0x519c, 0x06,"0100",eReadWrite},
  {0x519d, 0x82,"0100",eReadWrite},
  {0x519e, 0x38,"0100",eReadWrite},
  {0x5381, 0x1e,"0100",eReadWrite},
	{0x5382, 0x5b,"0100",eReadWrite},
	{0x5383, 0x16,"0100",eReadWrite},
	{0x5384, 0x03,"0100",eReadWrite},
	{0x5385, 0x76,"0100",eReadWrite},
	{0x5386, 0x79,"0100",eReadWrite},
	{0x5387, 0x7f,"0100",eReadWrite},
	{0x5388, 0x6e,"0100",eReadWrite},
	{0x5389, 0x11,"0100",eReadWrite},
	{0x538a, 0x01,"0100",eReadWrite},
	{0x538b, 0x98,"0100",eReadWrite},
  {0x5480, 0x01,"0100",eReadWrite},
  {0x5481, 0x08,"0100",eReadWrite},
  {0x5482, 0x14,"0100",eReadWrite},
  {0x5483, 0x28,"0100",eReadWrite},
  {0x5484, 0x48,"0100",eReadWrite},
  {0x5485, 0x59,"0100",eReadWrite},
  {0x5486, 0x66,"0100",eReadWrite},
  {0x5487, 0x73,"0100",eReadWrite},
  {0x5488, 0x7e,"0100",eReadWrite},
  {0x5489, 0x89,"0100",eReadWrite},
  {0x548a, 0x93,"0100",eReadWrite},
  {0x548b, 0xa4,"0100",eReadWrite},
  {0x548c, 0xb3,"0100",eReadWrite},
  {0x548d, 0xc9,"0100",eReadWrite},
  {0x548e, 0xda,"0100",eReadWrite},
  {0x548f, 0xe8,"0100",eReadWrite},
  {0x5490, 0x20,"0100",eReadWrite},
  {0x5300, 0x08,"0100",eReadWrite},
	{0x5301, 0x30,"0100",eReadWrite},
	{0x5302, 0x30,"0100",eReadWrite},
	{0x5303, 0x10,"0100",eReadWrite},
	{0x5304, 0x08,"0100",eReadWrite},
	{0x5305, 0x30,"0100",eReadWrite},
	{0x5306, 0x18,"0100",eReadWrite},
	{0x5307, 0x1c,"0100",eReadWrite},
	{0x5309, 0x08,"0100",eReadWrite},
	{0x530a, 0x30,"0100",eReadWrite},
	{0x530b, 0x04,"0100",eReadWrite},
	{0x530c, 0x06,"0100",eReadWrite},
  {0x5580, 0x06,"0100",eReadWrite},
  {0x5583, 0x40,"0100",eReadWrite},
  {0x5584, 0x10,"0100",eReadWrite},
  {0x5589, 0x10,"0100",eReadWrite},
  {0x558a, 0x00,"0100",eReadWrite},
  {0x558b, 0xf8,"0100",eReadWrite},
  {0x5000, 0xa7,"0100",eReadWrite},
  {0x5800, 0x33,"0100",eReadWrite},
  {0x5801, 0x2b,"0100",eReadWrite},
  {0x5802, 0x23,"0100",eReadWrite},
  {0x5803, 0x22,"0100",eReadWrite},
  {0x5804, 0x2b,"0100",eReadWrite},
  {0x5805, 0x34,"0100",eReadWrite},
  {0x5806, 0x21,"0100",eReadWrite},
  {0x5807, 0x11,"0100",eReadWrite},
  {0x5808, 0xb ,"0100",eReadWrite},
  {0x5809, 0xb ,"0100",eReadWrite},
  {0x580a, 0x11,"0100",eReadWrite},
  {0x580b, 0x1d,"0100",eReadWrite},
  {0x580c, 0x11,"0100",eReadWrite},
  {0x580d, 0x6 ,"0100",eReadWrite},
  {0x580e, 0x1 ,"0100",eReadWrite},
  {0x580f, 0x1 ,"0100",eReadWrite},
  {0x5810, 0x6 ,"0100",eReadWrite},
  {0x5811, 0x10,"0100",eReadWrite},
  {0x5812, 0x11,"0100",eReadWrite},
  {0x5813, 0x5 ,"0100",eReadWrite},
  {0x5814, 0x1 ,"0100",eReadWrite},
  {0x5815, 0x1 ,"0100",eReadWrite},
  {0x5816, 0x6 ,"0100",eReadWrite},
  {0x5817, 0xf ,"0100",eReadWrite},
  {0x5818, 0x20,"0100",eReadWrite},
  {0x5819, 0x10,"0100",eReadWrite},
  {0x581a, 0xa ,"0100",eReadWrite},
  {0x581b, 0xa ,"0100",eReadWrite},
  {0x581c, 0x10,"0100",eReadWrite},
  {0x581d, 0x1d,"0100",eReadWrite},
  {0x581e, 0x33,"0100",eReadWrite},
  {0x581f, 0x2a,"0100",eReadWrite},
  {0x5820, 0x20,"0100",eReadWrite},
  {0x5821, 0x1f,"0100",eReadWrite},
  {0x5822, 0x29,"0100",eReadWrite},
  {0x5823, 0x30,"0100",eReadWrite},
  {0x5824, 0x26,"0100",eReadWrite},
  {0x5825, 0xa ,"0100",eReadWrite},
  {0x5826, 0xa ,"0100",eReadWrite},
  {0x5827, 0xa ,"0100",eReadWrite},
  {0x5828, 0x6 ,"0100",eReadWrite},
  {0x5829, 0x28,"0100",eReadWrite},
  {0x582a, 0x4 ,"0100",eReadWrite},
  {0x582b, 0x4 ,"0100",eReadWrite},
  {0x582c, 0x4 ,"0100",eReadWrite},
  {0x582d, 0x28,"0100",eReadWrite},
  {0x582e, 0x26,"0100",eReadWrite},
  {0x582f, 0x22,"0100",eReadWrite},
  {0x5830, 0x20,"0100",eReadWrite},
  {0x5831, 0x22,"0100",eReadWrite},
  {0x5832, 0x6 ,"0100",eReadWrite},
  {0x5833, 0x28,"0100",eReadWrite},
  {0x5834, 0x4 ,"0100",eReadWrite},
  {0x5835, 0x4 ,"0100",eReadWrite},
  {0x5836, 0x4 ,"0100",eReadWrite},
  {0x5837, 0x2a,"0100",eReadWrite},
  {0x5838, 0x26,"0100",eReadWrite},
  {0x5839, 0xa ,"0100",eReadWrite},
  {0x583a, 0xa ,"0100",eReadWrite},
  {0x583b, 0xa ,"0100",eReadWrite},
  {0x583c, 0x8 ,"0100",eReadWrite},
  {0x583d, 0xee,"0100",eReadWrite},
  {0x5688, 0x11,"0100",eReadWrite},
  {0x5689, 0x11,"0100",eReadWrite},
  {0x568a, 0x11,"0100",eReadWrite},
  {0x568b, 0x11,"0100",eReadWrite},
  {0x568c, 0x11,"0100",eReadWrite},
  {0x568d, 0x11,"0100",eReadWrite},
  {0x568e, 0x11,"0100",eReadWrite},
  {0x568f, 0x11,"0100",eReadWrite},
  {0x5025, 0x00,"0100",eReadWrite},
  {0x3a0f, 0x38,"0100",eReadWrite},
	{0x3a10, 0x30,"0100",eReadWrite},
	{0x3a11, 0x61,"0100",eReadWrite},
	{0x3a1b, 0x38,"0100",eReadWrite},
	{0x3a1e, 0x30,"0100",eReadWrite},
	{0x3a1f, 0x10,"0100",eReadWrite}, 
  {0x4005, 0x18,"0100",eReadWrite},
  {0x3503, 0x00,"0100",eReadWrite},
  {0x3008, 0x02,"0100",eReadWrite},
  {0x501d, 0x10,"0100",eReadWrite},
	{0x5680, 0x00,"0100",eReadWrite}, 
	{0x5681, 0x00,"0100",eReadWrite},
	{0x5682, 0x00,"0100",eReadWrite},  
	{0x5683, 0x00,"0100",eReadWrite},
	{0x5684, 0x05,"0100",eReadWrite}, 
	{0x5685, 0x00,"0100",eReadWrite},
	{0x5686, 0x03,"0100",eReadWrite}, 
	{0x5687, 0xc0,"0100",eReadWrite},
//	{0x3406, 0xc0,"0100",eReadWrite},//awb	
																			  
{0x0000 ,0x00,"eTableEnd",eTableEnd}

};

const IsiRegDescription_t OV5645_g_twolane_resolution_1280_960[] =
{
	//;OV5645MIPI 1280x960,30fps
	//56Mhz, 224Mbps/Lane, 2Lane.
	{0x4202, 0x03,"0100",eReadWrite},
	{0x3008, 0x42,"0100",eReadWrite},	
	{0x3503, 0x00,"0100",eReadWrite},
//{0x3a00, 0x3c,"0100",eReadWrite}, 
  {0x5302, 0x30,"0100",eReadWrite},
	{0x5303, 0x10,"0100",eReadWrite},
	{0x5306, 0x18,"0100",eReadWrite},
	{0x5307, 0x1c,"0100",eReadWrite},
	{0x3600, 0x09,"0100",eReadWrite},
	{0x3601, 0x43,"0100",eReadWrite},
	{0x3820, 0x41,"0100",eReadWrite},//47
	{0x3821, 0x07,"0100",eReadWrite},//01
	{0x4514, 0x00,"0100",eReadWrite},
	{0x3800, 0x00,"0100",eReadWrite},
	{0x3801, 0x00,"0100",eReadWrite},
	{0x3802, 0x00,"0100",eReadWrite},
	{0x3803, 0x06,"0100",eReadWrite},
	{0x3804, 0x0a,"0100",eReadWrite},
	{0x3805, 0x3f,"0100",eReadWrite},
	{0x3806, 0x07,"0100",eReadWrite},
	{0x3807, 0x9d,"0100",eReadWrite},
	{0x3808, 0x05,"0100",eReadWrite},
	{0x3809, 0x00,"0100",eReadWrite},
	{0x380a, 0x03,"0100",eReadWrite},
	{0x380b, 0xc0,"0100",eReadWrite},	
	{0x3810, 0x00,"0100",eReadWrite},
	{0x3811, 0x10,"0100",eReadWrite},
	{0x3812, 0x00,"0100",eReadWrite},
	{0x3813, 0x06,"0100",eReadWrite},
	{0x3814, 0x31,"0100",eReadWrite},
	{0x3815, 0x31,"0100",eReadWrite},
	{0x3034, 0x18,"0100",eReadWrite},
  {0x3035, 0x11,"0100",eReadWrite},
  {0x3036, 0x38,"0100",eReadWrite},
  {0x3037, 0x13,"0100",eReadWrite},
	{0x380c, 0x07,"0100",eReadWrite},
	{0x380d, 0x68,"0100",eReadWrite},
	{0x380e, 0x03,"0100",eReadWrite},
	{0x380f, 0xd8,"0100",eReadWrite},
	{0x3a08, 0x01,"0100",eReadWrite},
	{0x3a09, 0x27,"0100",eReadWrite},
	{0x3a0e, 0x03,"0100",eReadWrite},
	{0x3a0a, 0x00,"0100",eReadWrite},
	{0x3a0b, 0xf6,"0100",eReadWrite},	
	{0x3a0d, 0x04,"0100",eReadWrite},
	{0x3618, 0x00,"0100",eReadWrite},		
	{0x3708, 0x66,"0100",eReadWrite},
	{0x3709, 0x52,"0100",eReadWrite},
	{0x370c, 0xc3,"0100",eReadWrite},
	{0x4004, 0x02,"0100",eReadWrite},		
	{0x460b, 0x37,"0100",eReadWrite},
	{0x460c, 0x20,"0100",eReadWrite},
	{0x4837, 0x11,"0100",eReadWrite},	
	{0x3824, 0x01,"0100",eReadWrite},
	{0x5001, 0xa3,"0100",eReadWrite},
	{0x5002, 0x80,"0100",eReadWrite},
	{0x5003, 0x08,"0100",eReadWrite},
	{0x3032, 0x00,"0100",eReadWrite},
//	{0x3008, 0x02,"0100",eReadWrite},

	{0x0000 ,0x00,"eTableEnd",eTableEnd}
};


const IsiRegDescription_t OV5645_g_twolane_resolution_2592_1944[] =
{
	//OV5645MIPI 2592x1944,10fps
	//90Mhz, 360Mbps/Lane, 2Lane.15

	  {0x4202, 0x03,"0100",eReadWrite},
	  {0x0 ,0x5,"0x0100",eDelay},//delay 5ms
	  {0x5302, 0x30,"0100",eReadWrite},
	  {0x5303, 0x10,"0100",eReadWrite},
	  {0x5306, 0x18,"0100",eReadWrite},
	  {0x5307, 0x1c,"0100",eReadWrite},
	  {0x3600, 0x08,"0100",eReadWrite},
	  {0x3601, 0x33,"0100",eReadWrite},
	  {0x3820, 0x40,"0100",eReadWrite},//46
	  {0x3821, 0x06,"0100",eReadWrite},//00
	  {0x4514, 0x00,"0100",eReadWrite},//88
	  {0x3800, 0x00,"0100",eReadWrite}, 
	  {0x3801, 0x00,"0100",eReadWrite}, 
	  {0x3802, 0x00,"0100",eReadWrite}, 
	  {0x3803, 0x00,"0100",eReadWrite}, 
	  {0x3804, 0x0a,"0100",eReadWrite},
	  {0x3805, 0x3f,"0100",eReadWrite},
	  {0x3806, 0x07,"0100",eReadWrite},
	  {0x3807, 0x9f,"0100",eReadWrite},
	  {0x3808, 0x0a,"0100",eReadWrite},
	  {0x3809, 0x20,"0100",eReadWrite},
	  {0x380a, 0x07,"0100",eReadWrite},
	  {0x380b, 0x98,"0100",eReadWrite},   
	  {0x3810, 0x00,"0100",eReadWrite},
	  {0x3811, 0x10,"0100",eReadWrite},
	  {0x3812, 0x00,"0100",eReadWrite},
	  {0x3813, 0x04,"0100",eReadWrite},
	  {0x3814, 0x11,"0100",eReadWrite},
	  {0x3815, 0x11,"0100",eReadWrite},
	  {0x3034, 0x18,"0100",eReadWrite},
	  {0x3035, 0x11,"0100",eReadWrite},//0x11=15fps,0x21=7.5fps
	  {0x3036, 0x5a,"0100",eReadWrite},
	  {0x3037, 0x13,"0100",eReadWrite},
	  {0x380c, 0x0b,"0100",eReadWrite},
	  {0x380d, 0xf0,"0100",eReadWrite},
	  {0x380e, 0x07,"0100",eReadWrite},
	  {0x380f, 0xb0,"0100",eReadWrite},
	  {0x3a08, 0x01,"0100",eReadWrite},
	  {0x3a09, 0x27,"0100",eReadWrite},
	  {0x3a0e, 0x06,"0100",eReadWrite},
	  {0x3a0a, 0x00,"0100",eReadWrite},
	  {0x3a0b, 0xf6,"0100",eReadWrite},   
	  {0x3a0d, 0x08,"0100",eReadWrite},
	  {0x3618, 0x04,"0100",eReadWrite},   
	  {0x3708, 0x63,"0100",eReadWrite},
	  {0x3709, 0x12,"0100",eReadWrite},
	  {0x370c, 0xc0,"0100",eReadWrite},
	  {0x4004, 0x06,"0100",eReadWrite},
	{0x460c, 0x20,"0100",eReadWrite}, 
	  {0x4837, 0x16,"0100",eReadWrite},   
	  {0x3824, 0x01,"0100",eReadWrite}, 
	  {0x5001, 0x83,"0100",eReadWrite},
	  {0x5002, 0x80,"0100",eReadWrite},
	  {0x5003, 0x08,"0100",eReadWrite},
	  {0x3032, 0x00,"0100",eReadWrite},

    {0x0000 ,0x00,"eTableEnd",eTableEnd}

};


