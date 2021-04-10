#pragma once

#define BIT(x) (1<<x)

#define DEGREE          BIT(0)
#define DIAMETER        BIT(1)
#define BTWN_CENT       BIT(2)
#define COMPONENTS      BIT(3)
#define GLOB_CLUSTER    BIT(4)
#define DEGENERACY      BIT(5)

#define INT_STATS (DEGREE+DIAMETER+COMPONENTS+DEGENERACY)
#define DOUBLE_STATS (BTWN_CENT+GLOB_CLUSTER)