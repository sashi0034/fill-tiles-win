
BurningFire = {}

local numFrame = 22

-- local calcScale = function (currTime, maxTime)
--     local percent = currTime / maxTime

--     local half = 0.3
--     if (percent<half) then
--         local quaterPeriod = half / 3
--         local onePeriod = quaterPeriod * 4

--         local theta = (2 * math.pi) * (percent / onePeriod)
--         local scale = 0.5 - 0.5 * math.cos(theta)
--         return scale
--     else
--         return 0.5
--     end

-- end

local function easeOutBack(x)
    local c1 = 1.70158 * 4;
    local c3 = c1 + 1;
    
    return 1 + c3 * (x-1)^3 + c1 * (x - 1)^2;
end

local function calcScale (currTime, maxTime)
    local percent = currTime / maxTime

    local half = 0.4

    if percent < half then
        return 0.5 * easeOutBack(percent / half)
    else
        return 0.5
    end
end


BurningFire.Update = function(
    lifetime,
    setApha,
    setFrame,
    setScale,
    destroy
)
    -- local newAlpha = lifetime * 1000;
    -- if newAlpha > 255 then newAlpha = 255 end
    setApha(255)

    local frameDuration = 0.05
    local currFrame = math.floor(lifetime/frameDuration)
    setFrame(currFrame)

    local maxLifetime = frameDuration * numFrame
    local scale = calcScale(lifetime, maxLifetime)
    setScale(scale, scale)

    if lifetime > maxLifetime then
        Println("destroy object")
        
        destroy()
    end
   

end

