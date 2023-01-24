GeoExplosion = {}


local function divideFloorly(value, maxValue, numDivision)
    while value>maxValue do
        value = value - maxValue
    end
    while value<0 do
        value = value + maxValue
    end

    local devidedVal = maxValue / numDivision

    return math.floor(value / devidedVal)
end


function GeoExplosion.Update(    
    lifetime,
    setApha,
    setFrame,
    setScale,
    destroy
)
    local span = 0.3
    setApha(255)

    setFrame(divideFloorly(lifetime, span, 4))

    if lifetime>0.3 then
        destroy()
    end
    
end


function GeoExplosion.ProduceEffects(
    yield,
    produce
)
    for count = 1, 10, 1 do
        for r = 0, 5, 1 do
            local radius = math.cos(count/10 * math.pi) * 32
            local theta = (r*60 + count * 15) / 180 * math.pi
            local dx = radius*math.cos(theta)
            local dy = radius*math.sin(theta)
            produce(dx, dy)
        end

        yield(0.05)
    end
end


