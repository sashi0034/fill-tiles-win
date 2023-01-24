
local function getYield(getDeltaTime)
    return function (waitTime)
        local countingTime = 0
        repeat
            coroutine.yield()
            countingTime = countingTime + getDeltaTime()
        until countingTime >= waitTime
    end
end

return getYield
