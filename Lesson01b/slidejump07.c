#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#define psvn2c_PSVN_API

#define HAVE_FWD_MOVE_PRUNING


/* number of variables in a state */
#define NUMVARS 7


typedef int8_t var_t;
#define PRI_VAR PRId8
#define SCN_VAR SCNd8

#define NUMDOMAINS 1
static var_t domain_sizes[ NUMDOMAINS ] = { 3 };
static int var_domains[ NUMVARS ] = { 0, 0, 0, 0, 0, 0, 0 };
static const char *domain_0[ 3 ] = {"R", "Y", "E" };
static const char **var_domain_names[ NUMVARS ] = { domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0 };

typedef struct {
 var_t vars[ NUMVARS ];
} state_t;

typedef int (*funcptr)( const state_t *, void * );
typedef void (*actfuncptr)( const state_t *, state_t * );

typedef struct {
 const state_t *my_state;
 funcptr my_funcptr;
} ruleid_iterator_t;

#define num_fwd_rules 22
static const char *fwd_rule_name[ 22 ] = { "rule_1", "rule_2", "rule_3", "rule_4", "rule_5", "rule_6", "rule_7", "rule_8", "rule_9", "rule_10", "rule_11", "rule_12", "rule_13", "rule_14", "rule_15", "rule_16", "rule_17", "rule_18", "rule_19", "rule_20", "rule_21", "rule_22" };
#define get_fwd_rule_label( ruleid ) (fwd_rule_name[(ruleid)]) 
#define cost_of_cheapest_fwd_rule 1
#define cost_of_costliest_fwd_rule 1
#define get_fwd_rule_cost( ruleid ) 1

static int fwd_prune_table[ 4554 ] = { 22, 418, 748, 1034, 1298, 1562, 1848, 2134, 2398, 2618, 2816, 3014, 3234, 3410, 3564, 3696, 3828, 3960, 4092, 4224, 4356, 4466, 0, 44, 66, 88, 110, 132, 0, 0, 154, 176, 198, 220, 0, 242, 264, 286, 308, 330, 0, 352, 374, 396, 0, 0, 462, 484, 506, 528, 0, 0, 0, 550, 572, 594, 0, 0, 616, 638, 660, 0, 682, 0, 704, 726, 0, 770, 0, 792, 814, 836, 0, 0, 0, 0, 880, 902, 0, 0, 0, 946, 968, 0, 0, 990, 0, 1012, 0, 0, 1056, 0, 1078, 1100, 0, 0, 0, 0, 0, 1166, 0, 1210, 0, 0, 1232, 1254, 0, 0, 1276, 0, 0, 0, 0, 1320, 0, 1342, 0, 0, 1408, 0, 0, 0, 0, 1452, 1474, 0, 0, 1496, 0, 0, 0, 1540, 0, 0, 0, 0, 1584, 0, 0, 0, 1650, 1672, 0, 0, 0, 1716, 1738, 1760, 0, 1782, 0, 1826, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2442, 2464, 2486, 0, 2508, 0, 0, 2530, 2552, 0, 0, 2574, 2596, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 2662, 2684, 0, 0, 2728, 0, 0, 2750, 0, 0, 0, 2794, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 2860, 0, 2904, 0, 2926, 0, 2948, 0, 2992, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 0, 3080, 3102, 0, 3124, 3146, 0, 3190, 3212, 0, 0, 0, 0, 3454, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 3498, 3520, 0, 0, 0, 0, 3542, 0, 3586, 0, 0, 3608, 0, 0, 0, 3630, 0, 0, 0, 0, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 3784, 0, 0, 0, 3806, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 3894, 0, 0, 3916, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4026, 4048, 4070, 0, 0, 0, 4246, 0, 0, 0, 0, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 4334, 0, 0, 0, 0, 4378, 0, 0, 0, 4400, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 440, 0, 462, 484, 506, 528, 0, 0, 0, 550, 572, 594, 0, 0, 616, 638, 660, 0, 682, 0, 704, 726, 0, 0, 66, 88, 110, 132, 0, 0, 0, 176, 198, 220, 0, 0, 264, 286, 308, 0, 0, 0, 374, 396, 0, 0, 0, 792, 814, 836, 0, 0, 0, 0, 880, 902, 0, 0, 0, 946, 968, 0, 0, 990, 0, 1012, 0, 0, 1056, 0, 1078, 1100, 0, 0, 0, 0, 0, 1166, 0, 0, 0, 0, 1232, 0, 0, 0, 1276, 0, 0, 0, 0, 1320, 0, 1342, 0, 0, 0, 0, 0, 0, 0, 0, 1474, 0, 0, 0, 1518, 0, 0, 1540, 0, 0, 0, 0, 1584, 0, 0, 0, 0, 1672, 0, 0, 0, 0, 1738, 1760, 0, 0, 1804, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2662, 2684, 0, 0, 2728, 0, 0, 0, 2772, 0, 0, 2794, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 2860, 0, 0, 0, 2926, 0, 0, 2970, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 0, 0, 3102, 0, 3124, 0, 3168, 0, 3212, 0, 0, 0, 0, 0, 3608, 0, 0, 0, 3630, 0, 0, 0, 0, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 3894, 0, 0, 0, 3938, 0, 0, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 4158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4180, 4202, 0, 0, 0, 0, 4378, 0, 0, 0, 0, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 4444, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 770, 0, 792, 814, 836, 858, 0, 0, 0, 880, 902, 924, 0, 0, 946, 968, 0, 0, 990, 0, 1012, 440, 0, 0, 484, 506, 528, 0, 0, 0, 0, 572, 594, 0, 0, 0, 638, 660, 0, 0, 0, 0, 726, 0, 0, 0, 0, 1078, 1100, 1122, 0, 0, 0, 0, 1166, 1188, 0, 0, 0, 1232, 0, 0, 0, 1276, 0, 0, 0, 0, 1320, 0, 1342, 1364, 0, 0, 0, 0, 0, 1430, 0, 0, 0, 0, 0, 0, 0, 0, 1540, 0, 0, 0, 0, 1584, 0, 1606, 0, 0, 0, 0, 0, 1694, 0, 0, 1760, 0, 0, 0, 1826, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1936, 1958, 0, 0, 0, 2002, 2024, 0, 0, 2068, 0, 2112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2860, 2882, 0, 0, 2926, 0, 0, 0, 2992, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 3058, 0, 0, 0, 3124, 0, 0, 3190, 0, 0, 0, 0, 0, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 0, 3322, 3344, 0, 0, 0, 0, 3388, 0, 0, 0, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4246, 0, 0, 0, 4268, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 4334, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 0, 0, 1056, 0, 1078, 1100, 1122, 1144, 0, 0, 0, 1166, 1188, 1210, 0, 0, 1232, 1254, 0, 0, 1276, 0, 0, 770, 0, 0, 814, 836, 858, 0, 0, 0, 0, 902, 924, 0, 0, 0, 968, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1342, 1364, 1386, 0, 0, 0, 0, 1430, 1452, 0, 0, 0, 1496, 0, 0, 0, 1540, 0, 0, 0, 0, 1584, 0, 1606, 1628, 0, 0, 0, 0, 1694, 1716, 0, 0, 0, 1782, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1870, 0, 0, 0, 1958, 0, 0, 0, 0, 2024, 0, 0, 0, 2090, 0, 0, 0, 0, 0, 0, 0, 2156, 0, 0, 0, 0, 2244, 2266, 0, 0, 0, 2310, 0, 0, 0, 2354, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3058, 3080, 0, 0, 3124, 3146, 0, 0, 3212, 0, 0, 0, 3256, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3344, 0, 0, 0, 3366, 0, 3432, 0, 0, 0, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 0, 3520, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 0, 0, 0, 3916, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4048, 0, 0, 0, 0, 0, 4378, 0, 0, 0, 4400, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 4444, 0, 0, 0, 0, 0, 0, 1320, 0, 1342, 1364, 1386, 1408, 0, 0, 0, 1430, 1452, 1474, 0, 0, 1496, 1518, 0, 0, 1540, 0, 0, 1056, 0, 0, 1100, 1122, 1144, 0, 0, 0, 0, 1188, 1210, 0, 0, 0, 1254, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1606, 1628, 1650, 0, 0, 0, 1694, 1716, 1738, 0, 0, 1782, 1804, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1870, 1892, 0, 0, 0, 0, 0, 1980, 0, 0, 0, 2046, 0, 0, 2112, 0, 0, 0, 0, 0, 0, 2156, 0, 2178, 0, 0, 0, 2266, 0, 0, 0, 0, 0, 0, 0, 0, 2376, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 0, 0, 0, 0, 2508, 0, 0, 0, 2552, 0, 0, 0, 2596, 0, 0, 3256, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 3300, 0, 0, 0, 0, 0, 0, 3388, 3432, 0, 0, 3454, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3542, 0, 3586, 0, 0, 0, 0, 0, 0, 3630, 0, 0, 0, 3652, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4070, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4202, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 0, 0, 0, 0, 1584, 0, 1606, 1628, 1650, 1672, 0, 0, 1694, 1716, 1738, 1760, 0, 1782, 1804, 1826, 0, 0, 0, 0, 0, 1320, 0, 0, 1364, 1386, 1408, 0, 0, 0, 1430, 1452, 1474, 0, 0, 1496, 1518, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1870, 1892, 1914, 0, 0, 0, 0, 1980, 2002, 0, 0, 2046, 2068, 0, 0, 0, 0, 0, 0, 0, 0, 2156, 0, 2178, 2200, 0, 0, 2266, 0, 0, 2288, 0, 0, 0, 2332, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 2442, 0, 0, 0, 2508, 0, 0, 0, 2552, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 0, 0, 2706, 0, 2728, 0, 0, 2750, 2772, 0, 0, 0, 0, 0, 3256, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 3300, 3322, 0, 0, 0, 0, 0, 0, 3432, 0, 0, 3454, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 3498, 0, 0, 0, 0, 0, 0, 0, 3586, 0, 0, 3608, 0, 0, 0, 3630, 0, 0, 0, 3652, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 0, 0, 0, 0, 3762, 0, 0, 0, 3784, 0, 0, 0, 3806, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4026, 0, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 4158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4246, 0, 0, 0, 4268, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1870, 1892, 1914, 1936, 1958, 0, 0, 1980, 2002, 2024, 0, 2046, 2068, 2090, 2112, 0, 0, 0, 0, 0, 0, 0, 0, 2178, 2200, 2222, 2244, 0, 0, 0, 2288, 2310, 0, 0, 2332, 2354, 2376, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 2442, 2464, 2486, 0, 0, 0, 0, 2530, 0, 0, 0, 2574, 2596, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 2662, 2684, 0, 0, 2728, 0, 0, 0, 2772, 0, 0, 2794, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 2860, 0, 0, 0, 2926, 0, 0, 2970, 2992, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 0, 0, 3102, 0, 3124, 0, 3168, 3190, 3212, 0, 0, 0, 0, 0, 3608, 0, 0, 0, 3630, 0, 0, 0, 0, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 3894, 0, 0, 0, 3938, 0, 0, 0, 0, 0, 4114, 0, 0, 0, 0, 0, 0, 4158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4180, 4202, 0, 0, 0, 4246, 0, 0, 0, 4268, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4334, 0, 0, 0, 0, 4378, 0, 0, 0, 4400, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 4444, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 0, 0, 0, 0, 0, 0, 2156, 0, 2178, 2200, 2222, 2244, 2266, 0, 0, 2288, 2310, 0, 0, 2332, 2354, 2376, 0, 0, 0, 0, 0, 0, 0, 0, 1892, 1914, 1936, 1958, 0, 0, 0, 2002, 2024, 0, 0, 2068, 2090, 2112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2442, 2464, 2486, 0, 0, 0, 0, 2530, 0, 0, 0, 2574, 2596, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 2662, 2684, 2706, 0, 0, 0, 0, 0, 0, 0, 0, 2794, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 2860, 2882, 0, 0, 2926, 0, 0, 0, 2992, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 3058, 0, 0, 0, 3124, 0, 0, 3190, 3212, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3300, 3322, 3344, 0, 0, 0, 3366, 3388, 0, 0, 0, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4246, 0, 0, 0, 0, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4334, 0, 0, 0, 0, 4378, 0, 0, 0, 4400, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 2442, 2464, 2486, 0, 2508, 0, 0, 2530, 2552, 0, 0, 2574, 2596, 0, 0, 0, 0, 0, 0, 2156, 0, 0, 2200, 2222, 2244, 0, 0, 0, 0, 2310, 0, 0, 0, 2354, 2376, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2662, 2684, 0, 0, 0, 0, 0, 2750, 0, 0, 0, 2794, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 2860, 0, 2904, 0, 0, 0, 2948, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 0, 3080, 0, 0, 3124, 3146, 0, 0, 3212, 0, 3432, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3498, 3520, 0, 0, 0, 0, 3542, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 0, 0, 0, 3916, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4048, 4070, 0, 0, 0, 0, 4378, 0, 0, 0, 0, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 2662, 2684, 2706, 0, 2728, 0, 0, 2750, 2772, 0, 0, 2794, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 0, 2464, 2486, 0, 0, 0, 0, 0, 2552, 0, 0, 0, 2596, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2860, 2882, 0, 0, 0, 0, 2948, 2970, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 3058, 0, 3102, 0, 0, 3146, 3168, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 3300, 0, 0, 0, 0, 0, 0, 3388, 0, 3586, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3652, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4070, 0, 0, 0, 0, 0, 0, 4136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4202, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 2860, 2882, 2904, 0, 2926, 0, 2948, 2970, 2992, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 0, 2684, 2706, 0, 0, 0, 0, 2750, 2772, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3058, 3080, 0, 0, 0, 3146, 3168, 3190, 0, 0, 0, 0, 3256, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 0, 3322, 0, 0, 0, 0, 0, 0, 3432, 0, 0, 0, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 3498, 0, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3784, 0, 0, 0, 3806, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4026, 0, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 4158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4268, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3036, 0, 3058, 3080, 3102, 0, 3124, 3146, 3168, 3190, 3212, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 0, 2882, 2904, 0, 0, 0, 2948, 2970, 2992, 0, 0, 0, 0, 3256, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 3300, 0, 3344, 0, 0, 0, 3366, 0, 3432, 0, 0, 3454, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 0, 3520, 0, 0, 0, 0, 0, 0, 3586, 0, 0, 0, 0, 0, 0, 3630, 0, 0, 0, 3652, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3894, 0, 0, 3916, 3938, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4026, 4048, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 4158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4180, 0, 0, 0, 0, 4246, 0, 0, 0, 4268, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4444, 0, 0, 0, 0, 0, 3256, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 3300, 3322, 3344, 0, 0, 0, 3366, 3388, 0, 0, 0, 792, 0, 0, 858, 0, 0, 0, 0, 0, 0, 0, 0, 946, 968, 0, 0, 990, 0, 1012, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1980, 2002, 2024, 0, 2046, 0, 2090, 2112, 0, 0, 0, 0, 3608, 0, 0, 0, 3630, 0, 0, 0, 0, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 3894, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4378, 0, 0, 0, 0, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3432, 0, 0, 3454, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 3498, 3520, 0, 0, 0, 0, 3542, 0, 0, 0, 88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 286, 308, 330, 0, 0, 0, 396, 0, 0, 0, 0, 1078, 0, 0, 1144, 0, 0, 0, 0, 0, 0, 0, 0, 1232, 0, 0, 0, 1276, 0, 0, 0, 0, 0, 0, 0, 2156, 0, 0, 0, 0, 0, 2266, 0, 0, 2288, 2310, 0, 0, 2332, 0, 2376, 0, 0, 0, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3586, 0, 0, 3608, 0, 0, 0, 3630, 0, 0, 0, 3652, 0, 0, 0, 3674, 0, 0, 0, 0, 0, 440, 0, 0, 0, 506, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 660, 0, 682, 0, 0, 0, 0, 0, 0, 0, 0, 1342, 0, 0, 1408, 0, 0, 0, 1430, 0, 0, 0, 0, 0, 0, 0, 0, 1540, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 0, 0, 0, 0, 2508, 0, 0, 2530, 2552, 0, 0, 2574, 0, 0, 0, 0, 0, 0, 0, 3278, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3344, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3718, 0, 0, 3740, 0, 0, 0, 3762, 0, 0, 0, 3784, 0, 0, 0, 3806, 0, 0, 0, 0, 0, 770, 0, 0, 0, 836, 0, 0, 0, 0, 0, 0, 924, 0, 0, 0, 0, 0, 0, 990, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1672, 0, 0, 0, 1716, 0, 0, 0, 1782, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 0, 0, 0, 0, 2728, 0, 0, 2750, 2772, 0, 0, 2794, 3432, 0, 0, 0, 0, 0, 0, 3476, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3850, 0, 0, 0, 0, 0, 0, 3872, 0, 0, 0, 3894, 0, 0, 3916, 3938, 0, 0, 0, 0, 0, 1056, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1210, 0, 0, 0, 1254, 0, 0, 1276, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2838, 0, 0, 0, 0, 0, 2926, 0, 2948, 2970, 2992, 0, 0, 0, 3586, 0, 0, 0, 0, 0, 0, 3630, 0, 0, 0, 3652, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 4004, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4026, 4048, 4070, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 616, 0, 0, 0, 682, 0, 704, 726, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2442, 0, 0, 0, 2508, 0, 0, 0, 0, 0, 0, 2574, 2596, 0, 0, 0, 4246, 0, 0, 0, 0, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4334, 0, 0, 0, 0, 4378, 0, 0, 0, 4400, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 4158, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4180, 4202, 0, 0, 0, 0, 0, 0, 858, 0, 0, 0, 0, 0, 924, 0, 0, 946, 0, 0, 0, 990, 0, 1012, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1914, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2090, 2112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2662, 0, 0, 0, 2728, 0, 0, 0, 0, 0, 0, 2794, 0, 0, 0, 0, 4378, 0, 0, 0, 0, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4246, 0, 0, 0, 4268, 0, 0, 4290, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 4334, 0, 0, 0, 0, 0, 0, 0, 1144, 0, 0, 0, 0, 0, 1210, 0, 0, 1232, 1254, 0, 0, 1276, 0, 0, 0, 0, 0, 0, 0, 2156, 0, 0, 0, 2222, 0, 2266, 0, 0, 0, 0, 0, 0, 0, 0, 2376, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2860, 0, 0, 0, 2926, 0, 2948, 0, 0, 0, 0, 0, 3982, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4070, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4378, 0, 0, 0, 4400, 0, 0, 4422, 0, 0, 0, 0, 0, 0, 4444, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1408, 0, 0, 0, 0, 0, 1474, 0, 0, 0, 1518, 0, 0, 1540, 0, 0, 0, 0, 0, 0, 0, 2420, 0, 0, 0, 2486, 0, 2508, 0, 0, 0, 2552, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3124, 0, 3168, 0, 0, 0, 0, 0, 4114, 0, 0, 0, 4136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4488, 0, 0, 0, 4510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4532, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1672, 0, 0, 0, 0, 0, 1760, 0, 0, 0, 1826, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2640, 0, 0, 0, 0, 0, 2728, 0, 0, 0, 2772, 0, 0, 0, 0, 0, 0, 4246, 0, 0, 0, 4268, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4312, 0, 0, 0, 0 };

static void fwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 2;
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 2;
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 2;
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 2;
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 2;
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 2;
  child_state->vars[ 6 ] = 0;
}

static void fwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 1;
  child_state->vars[ 1 ] = 2;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 1;
  child_state->vars[ 2 ] = 2;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 1;
  child_state->vars[ 3 ] = 2;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 1;
  child_state->vars[ 4 ] = 2;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 1;
  child_state->vars[ 5 ] = 2;
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 1;
  child_state->vars[ 6 ] = 2;
}

static void fwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 2;
  child_state->vars[ 1 ] = 1;
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 2;
  child_state->vars[ 2 ] = 1;
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule15( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 2;
  child_state->vars[ 3 ] = 1;
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule16( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 2;
  child_state->vars[ 4 ] = 1;
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule17( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 2;
  child_state->vars[ 5 ] = 1;
  child_state->vars[ 6 ] = 0;
}

static void fwdrule18( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 1;
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = 2;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule19( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 1;
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = 2;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule20( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 1;
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = 2;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule21( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 1;
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = 2;
  child_state->vars[ 6 ] = state->vars[ 6 ];
}

static void fwdrule22( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 1;
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = 2;
}

static actfuncptr fwd_rules[ 22 ] = { fwdrule1, fwdrule2, fwdrule3, fwdrule4, fwdrule5, fwdrule6, fwdrule7, fwdrule8, fwdrule9, fwdrule10, fwdrule11, fwdrule12, fwdrule13, fwdrule14, fwdrule15, fwdrule16, fwdrule17, fwdrule18, fwdrule19, fwdrule20, fwdrule21, fwdrule22 };

static int fwdfn5( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 2;
  } else {
    return -1;
  }
}

static int fwdfn7( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 6;
  } else {
    return -1;
  }
}

static int fwdfn6( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn7;
    return 2;
  } else {
    return fwdfn7( state, next_func );
  }
}

static int fwdfn9( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    return -1;
  case 1:
    *((funcptr *)next_func) = 0;
    return 18;
  default:
    *((funcptr *)next_func) = 0;
    return 2;
  }
}

static int fwdfn8( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn9;
    return 0;
  } else {
    return fwdfn9( state, next_func );
  }
}

static int fwdfn4( const state_t *state, void *next_func )
{
  switch( state->vars[ 1 ] ) {
  case 0:
    return fwdfn5( state, next_func );
  case 1:
    return fwdfn6( state, next_func );
  default:
    return fwdfn8( state, next_func );
  }
}

static int fwdfn3( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn4;
    return 5;
  } else {
    return fwdfn4( state, next_func );
  }
}

static int fwdfn12_a2_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 20;
}

static int fwdfn12( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn12_a2_1;
    return 2;
  } else {
    return -1;
  }
}

static int fwdfn13( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn12;
    return 6;
  } else {
    return fwdfn12( state, next_func );
  }
}

static int fwdfn15_a2_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 20;
}

static int fwdfn15( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    return -1;
  case 1:
    *((funcptr *)next_func) = 0;
    return 18;
  default:
    *((funcptr *)next_func) = fwdfn15_a2_1;
    return 2;
  }
}

static int fwdfn14( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn15;
    return 0;
  } else {
    return fwdfn15( state, next_func );
  }
}

static int fwdfn11( const state_t *state, void *next_func )
{
  switch( state->vars[ 1 ] ) {
  case 0:
    return fwdfn12( state, next_func );
  case 1:
    return fwdfn13( state, next_func );
  default:
    return fwdfn14( state, next_func );
  }
}

static int fwdfn10( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn11;
    return 16;
  } else {
    return fwdfn11( state, next_func );
  }
}

static int fwdfn16( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn4;
    return 11;
  } else {
    return fwdfn4( state, next_func );
  }
}

static int fwdfn2( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn3( state, next_func );
  case 1:
    return fwdfn10( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn16;
    return 4;
  }
}

static int fwdfn21( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 0;
  } else {
    return -1;
  }
}

static int fwdfn22( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 1 ) {
    *((funcptr *)next_func) = 0;
    return 6;
  } else {
    return -1;
  }
}

static int fwdfn20( const state_t *state, void *next_func )
{
  switch( state->vars[ 0 ] ) {
  case 0:
    return fwdfn21( state, next_func );
  case 1:
    return -1;
  default:
    return fwdfn22( state, next_func );
  }
}

static int fwdfn19( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn20;
    return 5;
  } else {
    return fwdfn20( state, next_func );
  }
}

static int fwdfn23( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn20;
    return 11;
  } else {
    return fwdfn20( state, next_func );
  }
}

static int fwdfn18( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn19( state, next_func );
  case 1:
    return fwdfn20( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn23;
    return 15;
  }
}

static int fwdfn26( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 5;
  } else {
    return -1;
  }
}

static int fwdfn27( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = 0;
    return 11;
  } else {
    return -1;
  }
}

static int fwdfn25( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn26( state, next_func );
  case 1:
    return -1;
  default:
    return fwdfn27( state, next_func );
  }
}

static int fwdfn28( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn25;
    return 6;
  } else {
    return fwdfn25( state, next_func );
  }
}

static int fwdfn29( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn25;
    return 0;
  } else {
    return fwdfn25( state, next_func );
  }
}

static int fwdfn24( const state_t *state, void *next_func )
{
  switch( state->vars[ 1 ] ) {
  case 0:
    return fwdfn25( state, next_func );
  case 1:
    return fwdfn28( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn29;
    return 18;
  }
}

static int fwdfn31( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn25;
    return 0;
  } else {
    return fwdfn25( state, next_func );
  }
}

static int fwdfn32( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn25;
    return 6;
  } else {
    return fwdfn25( state, next_func );
  }
}

static int fwdfn30( const state_t *state, void *next_func )
{
  switch( state->vars[ 0 ] ) {
  case 0:
    return fwdfn31( state, next_func );
  case 1:
    return fwdfn25( state, next_func );
  default:
    return fwdfn32( state, next_func );
  }
}

static int fwdfn17_a2_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn30;
  return 9;
}

static int fwdfn17( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    return fwdfn18( state, next_func );
  case 1:
    return fwdfn24( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn17_a2_1;
    return 2;
  }
}

static int fwdfn37( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = 0;
    return 0;
  } else {
    return -1;
  }
}

static int fwdfn36( const state_t *state, void *next_func )
{
  switch( state->vars[ 1 ] ) {
  case 0:
    return -1;
  case 1:
    return fwdfn7( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn37;
    return 18;
  }
}

static int fwdfn35( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    *((funcptr *)next_func) = fwdfn20;
    return 3;
  case 1:
    *((funcptr *)next_func) = fwdfn36;
    return 14;
  default:
    *((funcptr *)next_func) = fwdfn20;
    return 2;
  }
}

static int fwdfn34( const state_t *state, void *next_func )
{
  switch( state->vars[ 6 ] ) {
  case 0:
    return fwdfn35( state, next_func );
  case 1:
    *((funcptr *)next_func) = fwdfn35;
    return 21;
  default:
    *((funcptr *)next_func) = fwdfn35;
    return 5;
  }
}

static int fwdfn38( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn35;
    return 11;
  } else {
    return fwdfn35( state, next_func );
  }
}

static int fwdfn33( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn34( state, next_func );
  case 1:
    *((funcptr *)next_func) = fwdfn35;
    return 10;
  default:
    return fwdfn38( state, next_func );
  }
}

static int fwdfn1( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    return fwdfn2( state, next_func );
  case 1:
    return fwdfn17( state, next_func );
  default:
    return fwdfn33( state, next_func );
  }
}

static int fwdfn44( const state_t *state, void *next_func )
{
  switch( state->vars[ 6 ] ) {
  case 0:
    return -1;
  case 1:
    *((funcptr *)next_func) = 0;
    return 21;
  default:
    *((funcptr *)next_func) = 0;
    return 5;
  }
}

static int fwdfn43( const state_t *state, void *next_func )
{
  if( state->vars[ 4 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn44;
    return 3;
  } else {
    return fwdfn26( state, next_func );
  }
}

static int fwdfn46( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 16;
  } else {
    return -1;
  }
}

static int fwdfn45_a2_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 10;
}

static int fwdfn45( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    return fwdfn46( state, next_func );
  case 1:
    return -1;
  default:
    *((funcptr *)next_func) = fwdfn45_a2_1;
    return 3;
  }
}

static int fwdfn48( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    *((funcptr *)next_func) = 0;
    return 4;
  case 1:
    *((funcptr *)next_func) = 0;
    return 15;
  default:
    *((funcptr *)next_func) = 0;
    return 3;
  }
}

static int fwdfn47( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn48;
    return 11;
  } else {
    return fwdfn48( state, next_func );
  }
}

static int fwdfn42( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn43( state, next_func );
  case 1:
    return fwdfn45( state, next_func );
  default:
    return fwdfn47( state, next_func );
  }
}

static int fwdfn51( const state_t *state, void *next_func )
{
  if( state->vars[ 4 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 21;
  } else {
    return -1;
  }
}

static int fwdfn50( const state_t *state, void *next_func )
{
  switch( state->vars[ 6 ] ) {
  case 0:
    return -1;
  case 1:
    return fwdfn51( state, next_func );
  default:
    *((funcptr *)next_func) = 0;
    return 5;
  }
}

static int fwdfn52( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    return fwdfn46( state, next_func );
  case 1:
    return -1;
  default:
    *((funcptr *)next_func) = 0;
    return 10;
  }
}

static int fwdfn53( const state_t *state, void *next_func )
{
  if( state->vars[ 4 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn27;
    return 4;
  } else {
    return fwdfn27( state, next_func );
  }
}

static int fwdfn49( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn50( state, next_func );
  case 1:
    return fwdfn52( state, next_func );
  default:
    return fwdfn53( state, next_func );
  }
}

static int fwdfn55( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    return fwdfn26( state, next_func );
  case 1:
    *((funcptr *)next_func) = fwdfn26;
    return 9;
  default:
    return fwdfn44( state, next_func );
  }
}

static int fwdfn56( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    *((funcptr *)next_func) = fwdfn46;
    return 20;
  case 1:
    *((funcptr *)next_func) = 0;
    return 9;
  default:
    *((funcptr *)next_func) = 0;
    return 10;
  }
}

static int fwdfn58( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    *((funcptr *)next_func) = 0;
    return 4;
  case 1:
    *((funcptr *)next_func) = 0;
    return 9;
  default:
    return -1;
  }
}

static int fwdfn57( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn58;
    return 11;
  } else {
    return fwdfn58( state, next_func );
  }
}

static int fwdfn54( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn55( state, next_func );
  case 1:
    return fwdfn56( state, next_func );
  default:
    return fwdfn57( state, next_func );
  }
}

static int fwdfn41( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    return fwdfn42( state, next_func );
  case 1:
    return fwdfn49( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn54;
    return 13;
  }
}

static int fwdfn40( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn41;
    return 17;
  } else {
    return fwdfn41( state, next_func );
  }
}

static int fwdfn63( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 20;
  } else {
    return -1;
  }
}

static int fwdfn62( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn63;
    return 16;
  } else {
    return fwdfn63( state, next_func );
  }
}

static int fwdfn61( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn26( state, next_func );
  case 1:
    return fwdfn62( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn27;
    return 4;
  }
}

static int fwdfn66( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 2 ) {
    *((funcptr *)next_func) = 0;
    return 9;
  } else {
    return -1;
  }
}

static int fwdfn65( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn66;
    return 5;
  } else {
    return fwdfn66( state, next_func );
  }
}

static int fwdfn68( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    *((funcptr *)next_func) = 0;
    return 15;
  case 1:
    return -1;
  default:
    *((funcptr *)next_func) = 0;
    return 9;
  }
}

static int fwdfn67( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn68;
    return 11;
  } else {
    return fwdfn68( state, next_func );
  }
}

static int fwdfn64( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn65( state, next_func );
  case 1:
    return fwdfn66( state, next_func );
  default:
    return fwdfn67( state, next_func );
  }
}

static int fwdfn70( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn44( state, next_func );
  case 1:
    *((funcptr *)next_func) = 0;
    return 10;
  default:
    return fwdfn27( state, next_func );
  }
}

static int fwdfn69( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn70;
    return 3;
  } else {
    return fwdfn70( state, next_func );
  }
}

static int fwdfn60( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    return fwdfn61( state, next_func );
  case 1:
    return fwdfn64( state, next_func );
  default:
    return fwdfn69( state, next_func );
  }
}

static int fwdfn59( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn60;
    return 6;
  } else {
    return fwdfn60( state, next_func );
  }
}

static int fwdfn71( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn60;
    return 0;
  } else {
    return fwdfn60( state, next_func );
  }
}

static int fwdfn39( const state_t *state, void *next_func )
{
  switch( state->vars[ 1 ] ) {
  case 0:
    return fwdfn40( state, next_func );
  case 1:
    return fwdfn59( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn71;
    return 7;
  }
}

static int fwdfn76( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 1 ) {
    *((funcptr *)next_func) = 0;
    return 8;
  } else {
    return -1;
  }
}

static int fwdfn75( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn76;
    return 5;
  } else {
    return fwdfn76( state, next_func );
  }
}

static int fwdfn78( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    return -1;
  case 1:
    *((funcptr *)next_func) = 0;
    return 8;
  default:
    *((funcptr *)next_func) = 0;
    return 20;
  }
}

static int fwdfn77( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 2 ) {
    *((funcptr *)next_func) = fwdfn78;
    return 16;
  } else {
    return fwdfn78( state, next_func );
  }
}

static int fwdfn79( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 1 ) {
    *((funcptr *)next_func) = fwdfn27;
    return 8;
  } else {
    return fwdfn27( state, next_func );
  }
}

static int fwdfn74( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn75( state, next_func );
  case 1:
    return fwdfn77( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn79;
    return 4;
  }
}

static int fwdfn81( const state_t *state, void *next_func )
{
  switch( state->vars[ 5 ] ) {
  case 0:
    return fwdfn26( state, next_func );
  case 1:
    return -1;
  default:
    *((funcptr *)next_func) = fwdfn27;
    return 15;
  }
}

static int fwdfn80( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    *((funcptr *)next_func) = fwdfn81;
    return 19;
  case 1:
    *((funcptr *)next_func) = fwdfn25;
    return 8;
  default:
    *((funcptr *)next_func) = fwdfn25;
    return 9;
  }
}

static int fwdfn82( const state_t *state, void *next_func )
{
  switch( state->vars[ 3 ] ) {
  case 0:
    *((funcptr *)next_func) = fwdfn70;
    return 3;
  case 1:
    *((funcptr *)next_func) = fwdfn70;
    return 8;
  default:
    return fwdfn70( state, next_func );
  }
}

static int fwdfn73( const state_t *state, void *next_func )
{
  switch( state->vars[ 4 ] ) {
  case 0:
    return fwdfn74( state, next_func );
  case 1:
    return fwdfn80( state, next_func );
  default:
    return fwdfn82( state, next_func );
  }
}

static int fwdfn83( const state_t *state, void *next_func )
{
  switch( state->vars[ 0 ] ) {
  case 0:
    *((funcptr *)next_func) = fwdfn73;
    return 12;
  case 1:
    return fwdfn73( state, next_func );
  default:
    *((funcptr *)next_func) = fwdfn73;
    return 6;
  }
}

static int fwdfn84( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn73;
    return 0;
  } else {
    return fwdfn73( state, next_func );
  }
}

static int fwdfn72( const state_t *state, void *next_func )
{
  switch( state->vars[ 1 ] ) {
  case 0:
    *((funcptr *)next_func) = fwdfn73;
    return 1;
  case 1:
    return fwdfn83( state, next_func );
  default:
    return fwdfn84( state, next_func );
  }
}

static int fwdfn0( const state_t *state, void *next_func )
{
  switch( state->vars[ 2 ] ) {
  case 0:
    return fwdfn1( state, next_func );
  case 1:
    return fwdfn39( state, next_func );
  default:
    return fwdfn72( state, next_func );
  }
}


#define init_history 0

#define max_fwd_children 4

/* NOTE: FOR ALL OF THE MOVE ITERATOR DEFINITIONS funcptr
   MUST BE A VARIABLE. */

/* initialise a forward move iterator */
#define init_fwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = fwdfn0 ; \
  (*ruleid_iter).my_state = state; \
}

/* use iterator to generate next applicable rule to apply 
   returns rule to use, -1 if there are no more rules to apply */
#define next_ruleid( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

/* apply a rule to a state */
#define apply_fwd_rule( rule, state, result ) fwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define fwd_rule_valid_for_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_fwd_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])


/* returns 1 if state is a goal state, 0 otherwise */
static int is_goal( const state_t *state )
{
  if( state->vars[ 0 ] == 1 && state->vars[ 1 ] == 1 && state->vars[ 2 ] == 1 && state->vars[ 3 ] == 2 && state->vars[ 4 ] == 0 && state->vars[ 5 ] == 0 && state->vars[ 6 ] == 0 ) {
    return 1;
  }
  return 0;
}


/*
Copyright (C) 2011, 2014 by the PSVN Research Group, University of Alberta
*/

#include <string.h>

/* copy a state */
#define copy_state(dest_ptr,src_ptr) memcpy(dest_ptr,src_ptr,sizeof(var_t)*NUMVARS)

/* compare two state pointers
   returns 0 if equal, non-zero otherwise */
#define compare_states(a,b) memcmp(a,b,sizeof(var_t)*NUMVARS)


/* print a state to a file
   returns number of characters on success, -1 on failure */
static ssize_t print_state( FILE *file, const state_t *state )
{
  size_t len, t; int i;
  for( len = 0, i = 0; i < NUMVARS; ++i ) {
    t = fprintf( file, "%s ", var_domain_names[ i ][ state->vars[ i ] ] );
    if( t < 0 ) { return -1; }
    len += t;
  }
  return len;
}

/* print a state to a string
   returns number of characters on success, -1 on failure */
static ssize_t sprint_state( char *string,const size_t max_len,const state_t *state )
{
  size_t len, t; int i;
  for( len = 0, i = 0; i < NUMVARS; ++i ) {
    t = snprintf( &string[ len ], max_len - len, "%s ",
		  var_domain_names[ i ][ state->vars[ i ] ] );
    if( t < 0 ) { return -1; }
    len += t;
  }
  if( len >= max_len ) { return -1; } else { string[ len ] = 0; }
  return len;
}

/* read a state from a string
   returns number of characters consumed on success, -1 on failure
   NOTE: the part of the string representing the state must be
   followed either by whitespace (which will all be consumed) or
   the end of string marker */
static ssize_t read_state( const char *string, state_t *state )
{
  size_t len, t; int i; var_t j;
  len = 0;
  while( (string[len] !=0) && isspace(string[len]) ) { len++; } // skip leading white space
  for( i = 0; i < NUMVARS; ++i ) {
    for( j = 0; j < domain_sizes[ var_domains[ i ] ]; ++j ) {
      t = strlen( var_domain_names[ i ][ j ] );
      if( !strncasecmp( var_domain_names[ i ][ j ], &string[ len ], t ) ) {
          if( (string[len+t] ==0) || isspace(string[len+t]) ) { // require a terminator after the match
	      state->vars[ i ] = j;
	      len += t;
              while( (string[len] !=0) && isspace(string[len]) ) { len++; } // skip the following white space
              break;
          }
      }
    }
    if( j >= domain_sizes[ var_domains[ i ] ] ) { return -1; }
  }
  return len;
}

/* dump a raw state to a file
   returns 1 on success, 0 on failure */
#define dump_state( file, state_ptr ) fwrite(state_ptr,sizeof(var_t)*NUMVARS,1,file)

/* load a raw state from a file
   returns 1 on success, 0 on failure */
#define load_state( file, state_ptr ) fread(state_ptr,sizeof(var_t)*NUMVARS,1,file)




/*
-------------------------------------------------------------------------------
lookup3.c, by Bob Jenkins, May 2006, Public Domain.

These are functions for producing 32-bit hashes for hash table lookup.
hashword(), hashlittle(), hashlittle2(), hashbig(), mix(), and final() 
are externally useful functions.  Routines to test the hash are included 
if SELF_TEST is defined.  You can use this free for any purpose.  It's in
the public domain.  It has no warranty.

You probably want to use hashlittle().  hashlittle() and hashbig()
hash byte arrays.  hashlittle() is is faster than hashbig() on
little-endian machines.  Intel and AMD are little-endian machines.
On second thought, you probably want hashlittle2(), which is identical to
hashlittle() except it returns two 32-bit hashes for the price of one.  
You could implement hashbig2() if you wanted but I haven't bothered here.

If you want to find a hash of, say, exactly 7 integers, do
  a = i1;  b = i2;  c = i3;
  mix(a,b,c);
  a += i4; b += i5; c += i6;
  mix(a,b,c);
  a += i7;
  final(a,b,c);
then use c as the hash value.  If you have a variable length array of
4-byte integers to hash, use hashword().  If you have a byte array (like
a character string), use hashlittle().  If you have several byte arrays, or
a mix of things, see the comments above hashlittle().  

Why is this so big?  I read 12 bytes at a time into 3 4-byte integers, 
then mix those integers.  This is fast (you can do a lot more thorough
mixing with 12*3 instructions on 3 integers than you can with 3 instructions
on 1 byte), but shoehorning those bytes into integers efficiently is messy.
-------------------------------------------------------------------------------
*/
#include <sys/param.h>  /* attempt to define endianness */
#ifdef linux
# include <endian.h>    /* attempt to define endianness */
#endif

/*
 * My best guess at if you are big-endian or little-endian.  This may
 * need adjustment.
 */
#if (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && \
     __BYTE_ORDER == __LITTLE_ENDIAN) || \
    (defined(i386) || defined(__i386__) || defined(__i486__) || \
     defined(__i586__) || defined(__i686__) || defined(vax) || defined(MIPSEL))
# define HASH_LITTLE_ENDIAN 1
# define HASH_BIG_ENDIAN 0
#elif (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && \
       __BYTE_ORDER == __BIG_ENDIAN) || \
      (defined(sparc) || defined(POWERPC) || defined(mc68000) || defined(sel))
# define HASH_LITTLE_ENDIAN 0
# define HASH_BIG_ENDIAN 1
#else
# define HASH_LITTLE_ENDIAN 0
# define HASH_BIG_ENDIAN 0
#endif

#define rot(x,k) (((x)<<(k)) ^ ((x)>>(32-(k))))

/*
-------------------------------------------------------------------------------
mix -- mix 3 32-bit values reversibly.

This is reversible, so any information in (a,b,c) before mix() is
still in (a,b,c) after mix().

If four pairs of (a,b,c) inputs are run through mix(), or through
mix() in reverse, there are at least 32 bits of the output that
are sometimes the same for one pair and different for another pair.
This was tested for:
* pairs that differed by one bit, by two bits, in any combination
  of top bits of (a,b,c), or in any combination of bottom bits of
  (a,b,c).
* "differ" is defined as +, -, ^, or ~^.  For + and -, I transformed
  the output delta to a Gray code (a^(a>>1)) so a string of 1's (as
  is commonly produced by subtraction) look like a single 1-bit
  difference.
* the base values were pseudorandom, all zero but one bit set, or 
  all zero plus a counter that starts at zero.

Some k values for my "a-=c; a^=rot(c,k); c+=b;" arrangement that
satisfy this are
    4  6  8 16 19  4
    9 15  3 18 27 15
   14  9  3  7 17  3
Well, "9 15 3 18 27 15" didn't quite get 32 bits diffing
for "differ" defined as + with a one-bit base and a two-bit delta.  I
used http://burtleburtle.net/bob/hash/avalanche.html to choose 
the operations, constants, and arrangements of the variables.

This does not achieve avalanche.  There are input bits of (a,b,c)
that fail to affect some output bits of (a,b,c), especially of a.  The
most thoroughly mixed value is c, but it doesn't really even achieve
avalanche in c.

This allows some parallelism.  Read-after-writes are good at doubling
the number of bits affected, so the goal of mixing pulls in the opposite
direction as the goal of parallelism.  I did what I could.  Rotates
seem to cost as much as shifts on every machine I could lay my hands
on, and rotates are much kinder to the top and bottom bits, so I used
rotates.
-------------------------------------------------------------------------------
*/
#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}

/*
-------------------------------------------------------------------------------
final -- final mixing of 3 32-bit values (a,b,c) into c

Pairs of (a,b,c) values differing in only a few bits will usually
produce values of c that look totally different.  This was tested for
* pairs that differed by one bit, by two bits, in any combination
  of top bits of (a,b,c), or in any combination of bottom bits of
  (a,b,c).
* "differ" is defined as +, -, ^, or ~^.  For + and -, I transformed
  the output delta to a Gray code (a^(a>>1)) so a string of 1's (as
  is commonly produced by subtraction) look like a single 1-bit
  difference.
* the base values were pseudorandom, all zero but one bit set, or 
  all zero plus a counter that starts at zero.

These constants passed:
 14 11 25 16 4 14 24
 12 14 25 16 4 14 24
and these came close:
  4  8 15 26 3 22 24
 10  8 15 26 3 22 24
 11  8 15 26 3 22 24
-------------------------------------------------------------------------------
*/
#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

/*
 * hashlittle2: return 2 32-bit hash values
 *
 * This is identical to hashlittle(), except it returns two 32-bit hash
 * values instead of just one.  This is good enough for hash table
 * lookup with 2^^64 buckets, or if you want a second hash if you're not
 * happy with the first, or if you want a probably-unique 64-bit ID for
 * the key.  *pc is better mixed than *pb, so use *pc first.  If you want
 * a 64-bit value do something like "*pc + (((uint64_t)*pb)<<32)".
 */
static void hashlittle2( 
  const void *key,       /* the key to hash */
  size_t      length,    /* length of the key */
  uint32_t   *pc,        /* IN: primary initval, OUT: primary hash */
  uint32_t   *pb)        /* IN: secondary initval, OUT: secondary hash */
{
  uint32_t a,b,c;                                          /* internal state */
  union { const void *ptr; size_t i; } u;     /* needed for Mac Powerbook G4 */

  /* Set up the internal state */
  a = b = c = 0xdeadbeef + ((uint32_t)length) + *pc;
  c += *pb;

  u.ptr = key;
  if (HASH_LITTLE_ENDIAN && ((u.i & 0x3) == 0)) {
    const uint32_t *k = (const uint32_t *)key;         /* read 32-bit chunks */
#ifdef VALGRIND
    const uint8_t  *k8;
#endif

    /*------ all but last block: aligned reads and affect 32 bits of (a,b,c) */
    while (length > 12)
    {
      a += k[0];
      b += k[1];
      c += k[2];
      mix(a,b,c);
      length -= 12;
      k += 3;
    }

    /*----------------------------- handle the last (probably partial) block */
    /* 
     * "k[2]&0xffffff" actually reads beyond the end of the string, but
     * then masks off the part it's not allowed to read.  Because the
     * string is aligned, the masked-off tail is in the same word as the
     * rest of the string.  Every machine with memory protection I've seen
     * does it on word boundaries, so is OK with this.  But VALGRIND will
     * still catch it and complain.  The masking trick does make the hash
     * noticably faster for short strings (like English words).
     */
#ifndef VALGRIND

    switch(length)
    {
    case 12: c+=k[2]; b+=k[1]; a+=k[0]; break;
    case 11: c+=k[2]&0xffffff; b+=k[1]; a+=k[0]; break;
    case 10: c+=k[2]&0xffff; b+=k[1]; a+=k[0]; break;
    case 9 : c+=k[2]&0xff; b+=k[1]; a+=k[0]; break;
    case 8 : b+=k[1]; a+=k[0]; break;
    case 7 : b+=k[1]&0xffffff; a+=k[0]; break;
    case 6 : b+=k[1]&0xffff; a+=k[0]; break;
    case 5 : b+=k[1]&0xff; a+=k[0]; break;
    case 4 : a+=k[0]; break;
    case 3 : a+=k[0]&0xffffff; break;
    case 2 : a+=k[0]&0xffff; break;
    case 1 : a+=k[0]&0xff; break;
    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
    }

#else /* make valgrind happy */

    k8 = (const uint8_t *)k;
    switch(length)
    {
    case 12: c+=k[2]; b+=k[1]; a+=k[0]; break;
    case 11: c+=((uint32_t)k8[10])<<16;  /* fall through */
    case 10: c+=((uint32_t)k8[9])<<8;    /* fall through */
    case 9 : c+=k8[8];                   /* fall through */
    case 8 : b+=k[1]; a+=k[0]; break;
    case 7 : b+=((uint32_t)k8[6])<<16;   /* fall through */
    case 6 : b+=((uint32_t)k8[5])<<8;    /* fall through */
    case 5 : b+=k8[4];                   /* fall through */
    case 4 : a+=k[0]; break;
    case 3 : a+=((uint32_t)k8[2])<<16;   /* fall through */
    case 2 : a+=((uint32_t)k8[1])<<8;    /* fall through */
    case 1 : a+=k8[0]; break;
    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
    }

#endif /* !valgrind */

  } else if (HASH_LITTLE_ENDIAN && ((u.i & 0x1) == 0)) {
    const uint16_t *k = (const uint16_t *)key;         /* read 16-bit chunks */
    const uint8_t  *k8;

    /*--------------- all but last block: aligned reads and different mixing */
    while (length > 12)
    {
      a += k[0] + (((uint32_t)k[1])<<16);
      b += k[2] + (((uint32_t)k[3])<<16);
      c += k[4] + (((uint32_t)k[5])<<16);
      mix(a,b,c);
      length -= 12;
      k += 6;
    }

    /*----------------------------- handle the last (probably partial) block */
    k8 = (const uint8_t *)k;
    switch(length)
    {
    case 12: c+=k[4]+(((uint32_t)k[5])<<16);
             b+=k[2]+(((uint32_t)k[3])<<16);
             a+=k[0]+(((uint32_t)k[1])<<16);
             break;
    case 11: c+=((uint32_t)k8[10])<<16;     /* fall through */
    case 10: c+=k[4];
             b+=k[2]+(((uint32_t)k[3])<<16);
             a+=k[0]+(((uint32_t)k[1])<<16);
             break;
    case 9 : c+=k8[8];                      /* fall through */
    case 8 : b+=k[2]+(((uint32_t)k[3])<<16);
             a+=k[0]+(((uint32_t)k[1])<<16);
             break;
    case 7 : b+=((uint32_t)k8[6])<<16;      /* fall through */
    case 6 : b+=k[2];
             a+=k[0]+(((uint32_t)k[1])<<16);
             break;
    case 5 : b+=k8[4];                      /* fall through */
    case 4 : a+=k[0]+(((uint32_t)k[1])<<16);
             break;
    case 3 : a+=((uint32_t)k8[2])<<16;      /* fall through */
    case 2 : a+=k[0];
             break;
    case 1 : a+=k8[0];
             break;
    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
    }

  } else {                        /* need to read the key one byte at a time */
    const uint8_t *k = (const uint8_t *)key;

    /*--------------- all but the last block: affect some 32 bits of (a,b,c) */
    while (length > 12)
    {
      a += k[0];
      a += ((uint32_t)k[1])<<8;
      a += ((uint32_t)k[2])<<16;
      a += ((uint32_t)k[3])<<24;
      b += k[4];
      b += ((uint32_t)k[5])<<8;
      b += ((uint32_t)k[6])<<16;
      b += ((uint32_t)k[7])<<24;
      c += k[8];
      c += ((uint32_t)k[9])<<8;
      c += ((uint32_t)k[10])<<16;
      c += ((uint32_t)k[11])<<24;
      mix(a,b,c);
      length -= 12;
      k += 12;
    }

    /*-------------------------------- last block: affect all 32 bits of (c) */
    switch(length)                   /* all the case statements fall through */
    {
    case 12: c+=((uint32_t)k[11])<<24;
    case 11: c+=((uint32_t)k[10])<<16;
    case 10: c+=((uint32_t)k[9])<<8;
    case 9 : c+=k[8];
    case 8 : b+=((uint32_t)k[7])<<24;
    case 7 : b+=((uint32_t)k[6])<<16;
    case 6 : b+=((uint32_t)k[5])<<8;
    case 5 : b+=k[4];
    case 4 : a+=((uint32_t)k[3])<<24;
    case 3 : a+=((uint32_t)k[2])<<16;
    case 2 : a+=((uint32_t)k[1])<<8;
    case 1 : a+=k[0];
             break;
    case 0 : *pc=c; *pb=b; return;  /* zero length strings require no mixing */
    }
  }

  final(a,b,c);
  *pc=c; *pb=b; return;             /* zero length strings require no mixing */
}
/* ----------------------------------------------------------------------
   end lookup3
   ---------------------------------------------------------------------- */





static uint64_t hash_state( const state_t *state )
{
  uint32_t a, b;

  a = 0; b = 0; hashlittle2( state, sizeof( var_t ) * NUMVARS, &a, &b );
  return ( (uint64_t)a << 32 ) | b;
}




