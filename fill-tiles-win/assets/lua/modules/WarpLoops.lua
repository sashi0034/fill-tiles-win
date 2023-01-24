
WarpLoops = {}

WarpLoops.ProducingDuration = 0.3

function WarpLoops.Update(    
    lifetime,
    setAlpha,
    setPos,
    destroy
)
    local upHeight = 16.0
    local alphaTime = 0.3
    local lifetimeMax = 1.0

    if lifetime > lifetimeMax then
        destroy()
        return
    end

    local percent = lifetime / lifetimeMax
    setPos(0, -upHeight * percent)

    if lifetime < alphaTime then
        setAlpha(255*lifetime / alphaTime)
    elseif lifetime > lifetimeMax - alphaTime then
        setAlpha(255* (lifetimeMax - lifetime) / alphaTime)
    else
        setAlpha(255);
    end

    
end

WarpLoops = require("fixReadonly")(WarpLoops)
