quadratic <- function(coeff)
{
    a <- coeff[1]
    b<- coeff[2]
    c <- coeff[3]
    d <- b^2 - (4*a*c)
    cat("The discriminant is: ",d,"\n")
    if(d<0)
     cat("There are no real roots. ","\n")
    if(d >= 0)
    {
        root1 <- (-b + sqrt(d)) / (2*a)
        root2 <- (-b - sqrt(d)) / (2*a)
        cat("root1: ", root1, "\n")
        cat("root2: ", root2, "\n")
    }
}

info <- list(name = "Ray", gender = "Male", age = 52, salary = 38500)
class(info) <- "member"
attributes(info)


print.member <- function(person)
{
    cat(person$name, "\n")
    cat("gender", person$sex, "\n")
    cat("age", person$age, "\n")
    cat("salary", person$salary, "\n")
}

setClass("member",
         representation(
             name = "character",
             sex = "character",
             age = "numeric",
             salary = "numeric"
         )
)




