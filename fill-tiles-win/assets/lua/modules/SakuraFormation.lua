
SakuraFormation = {}



local function easeOutBack(x)
    local c1 = 1.70158 * 4;
    local c3 = c1 + 1;
    
    return 1 + c3 * (x-1)^3 + c1 * (x - 1)^2;
end

function SakuraFormation.Update(    
    lifetime,
    setAlpha,
    setFrame,
    setScale,
    setRotation,
    destroy
)
    local scalingTime = 0.3
    local fadeTime = 0.2
    local lifetimeMax = scalingTime + fadeTime

    setFrame(1)
    
    setRotation(lifetime*720)

    if lifetime < scalingTime then
        local t = lifetime
        local scale = 1 * easeOutBack(t/scalingTime)
        setScale(scale, scale)            
        setAlpha(255)
    elseif lifetime < lifetimeMax then
        local t = lifetime - scalingTime
        local percent = 1 - t / fadeTime
        setAlpha(255*percent)
    else
        destroy()
        return
    end

    
end


function SakuraFormation.ProduceEffects(
    yield,
    produce
)
    for count = 1, 8, 1 do
        local numRound = 5
        for r = 0, numRound-1, 1 do
            local radius = math.cos(count/8 * math.pi) * 48
            local theta = (r*(360/numRound) + count * (360/numRound/4)) / 180 * math.pi
            local dx = radius*math.sin(theta)
            local dy = radius*math.cos(theta)
            produce(dx, dy)
        end

        yield(0.05)
    end
end



