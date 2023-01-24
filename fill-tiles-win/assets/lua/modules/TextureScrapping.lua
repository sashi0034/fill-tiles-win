
TextureScrapping = {}

TextureScrapping.InitialVelocity = 50.0

TextureScrapping.InitialVerticalForce = -50

TextureScrapping.FocalLength = 0.5

TextureScrapping.Gravity = 500.0

TextureScrapping.MaxLifetime = 0.8

local fixReadonly = require "fixReadonly"
TextureScrapping = fixReadonly(TextureScrapping)

