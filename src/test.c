#include <stdio.h>
#include <time.h>

int	main(void)
{
	time_t		seconds_since_epoch;
	struct tm	*dt;

	// UNIXエポックからの秒数
	seconds_since_epoch = 1715688910;
	// time_tからstruct tmへの変換
	dt = localtime(&seconds_since_epoch);
	// 日時の表示
	printf("Year: %d\n", dt->tm_year + 1900); // tm_yearは1900からの年数
	printf("Month: %d\n", dt->tm_mon + 1);    // tm_monは0から始まる月
	printf("Day: %d\n", dt->tm_mday);
	printf("Hour: %d\n", dt->tm_hour);
	printf("Minute: %d\n", dt->tm_min);
	printf("Second: %d\n", dt->tm_sec);
	return (0);
}
