BefOpt <- c(10842, 8343, 7680, 7462, 12803, 7369, 7984 ,7539, 11342, 7424 )
AftOpt <- c(3601, 3433, 4498, 4854, 3442, 4213, 3825, 3641, 3424, 3871)
OptB <- c(3560, 3941, 3359, 3657, 3910, 3651, 4368, 4039, 3518, 4422 )
 OptBxBy <-c(4054, 3627, 3880, 3559, 3943, 4000, 3507, 3741, 3474, 3472)

boxplot(cbind(BefOpt,AftOpt,OptB,OptBxBy) , ylab = "Time(us)", 
        names=c("Before Optimization", "After Optimization", "After Optimization B=16", "After Optimization 2 dimensions") 
        ,col="orange")
