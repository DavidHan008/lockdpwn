
=======================================================================
$$$$ R Language programming $$$$ 161229수~
=======================================================================


$ attach(Mileage) ==> Mileage 데이터셋의 각 변수들을 불러온다

$ cat(...)  ==> printf()와 같은 함수인듯

$ any(results == 0) ==> results 값에 0이 하나라도 포함되어 있다면 TRUE 반환

$ which(results ==0) ==> results가 0이 처음 나올때 위치값

$ all(primes %% 2 == 0) ==> primes를 2로 나눈 나머지가 전부 0 이면 TRUE 반환

$ summary(percapita[2:9])  ==> 요약정보, 

$ colMeans(percapita[2:9]) ==> 각 열의 평균값

$ quantile(percapita[,9]) ==> 전체 데이터의 분위수를 구하는 함수 (분위수?)

$ scale(percapita[,9])  ==> percapita[,9] 데이터를 표준정규분포화한다

$ sd(percapita[,9]) ==> 표준편차를 구한다 

$ var(percapita[,9]) ==> 분산을 구한다

$ mad(weights) ==> 중앙값의 절대편차

$ p,d,r,q 확률분포 관련 함수 

$ dbinom(8, size = 10, prob=0.76) ==> 이항분포

$ dpois(xvec,25) ==> 푸아송 분포

$ t.test(Posttest) ==> t 검증











=======================================================================

$ seq(5,9,0.5)  ==> 5부터 9까지 0.5단위로 수를 생성합니다

$ rep("yo",times == 3) ==> yo 문자를 3번 출력합니다


$ persp(plank) ==> plank 행렬을 도식화한다
$ contour(plank) ==> plank 행렬을 도식화한다2
$ image(plank) ==> plank 행렬을 이미지로 표시한다









=======================================================================
# z분포와 t분포의 비교 (색상있는게 자유도별 t분포이다)
x <- seq(-3.5,3.5,.1)
y1 <- dnorm(x)
y2 <- dt(x,4)
y3 <- dt(x,9)
y4 <- dt(x,19)

plot(x,y1,type="l")
points(x,y2,type="l",col = "red")
points(x,y3,type="l",col = "green")
points(x,y4,type="l",col = "blue")



=======================================================================
# 신뢰구간에서 E값을 적절하게 선택할 경우 필요한 표본의 갯수를 구하는 함수
sampsize.est <- function(E, sigma, alpha = .05)
{
    n <- ((qnorm(alpha/2) * sigma)/E)^2
    estsize <- ceiling(n)
    
    cat("for a desired margin of error of: ",E,"the required sample size is: ",estsize,"\n")
}





=======================================================================
# 마프응 중간기말 성적 난 [93,71]
micromid <- c(77.5,45.5,95,70.5,77,63,56,82,85,49,89,66,0,73.5,101.5,50.5,78,73,58,83.5,79,88.5,85,91,46.5,81,88,61,91,0,93,63.5,75,0,94,76,36.5,94,57,75,98,80,42,64,89,72)
microfinal <- c(64,58,77,56,54,49,71,74,74,51,77,55,0,67,77,59,67,65,60,69,71,70,68,67,49,79,75,57,66,0,71,69,53,0,74,63,49,80,60,68,72,78,51,61,67,73)
micrototal <- micromid + microfinal

std <- sd(micrototal)
z <- scale(164, center = 130.6, scale = std)
pnorm(z)

# 백분위 78.5% 에 들었다 (70%까지 A+ 인듯)








=======================================================================
# 평균 절대편차를 구하는 함수
MeanAbsDev <- function(x)
{
	AbsDev <- abs(x - mean(x))
	MAD <- mean(AbsDev)
	cat("The mean absolute deviation is: ",MAD,"\n")
} 






=======================================================================
# 중앙값 절대편차 mad() 함수 -> 이미 구현되어 있다 
mad <- function(x, center = median(x), constant = 1.4826, na.rm = FALSE , low = FALSE, high = FALSE)
{
    if(na.rm)
    {
        x <- x[!is.na(x)]
    }
    n <- length(x)
    
    constant *if((low || high) && n%%2 == 0)
    {
        if(low && high)
        {
            stop("'low' and 'high' connaot be both TRUE")
        }
        n2 <- n%/%2 + as.integer(high)
        sort(abs(x - center), partial = n2)[n2]
    }
    else median (abs(x - center))
}




=======================================================================
# t분포를 사용한 평균의 신뢰구간 
# a-risk는 기본적으로 0.05이다
# 좀 수정하면 t.test() 함수와 유사한 기능을 할 수 있지만 코드량이 많이 늘어난다. 책참조
confint <- function(x, alpha = .05)
{
    conflevel = (1 - alpha) * 100
    stderr <- sd(x) / sqrt(length(x))
    tcrit <- qt(1 - alpha/2, length(x)-1)
    
    margin <- stderr * tcrit
    lower <- mean(x) - margin
    upper <- mean(x) + margin
    
    cat(conflevel,"Percent Confidence Interval","\n")
    cat("Mean: ", mean(x), "Std.Error: ", stderr,"\n")
    cat("Lower Limit: ", lower, "\n")
    cat("Upper Limit: ", upper, "\n")
}	




=======================================================================
# 숫자가 소수인지 검사하는 함수
primality <- function(x)
{
	# 2보다 작으면 멈춘다
    stopifnot(x >= 2)

    limit <- trunc(sqrt(x) +1)
    
    testvec <- 2:limit
    results <- x %% testvec

	# 결과에 0 값이 하나라도 포함되어 있다면 any()
    check <- any(results == 0)
    outcome <- "Yes."
    
    if(check == TRUE) outcome <- "No."
    if(x == 2) outcome <- "Yes."
    
    cat("Is",x,"prime?",outcome,"\n")
}







