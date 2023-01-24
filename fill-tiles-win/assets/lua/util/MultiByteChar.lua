
MultiByteChar = {}

function MultiByteChar.Length(str)
    return utf8.len(str)
end

function MultiByteChar.GetAt(str, index)
    local lead = utf8.offset(str, index, 1)
    local trail = utf8.offset(str, index+1, 1) - 1
    return string.sub(str, lead, trail)
end

