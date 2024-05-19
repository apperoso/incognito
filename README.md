# Incognito
A type-erased identifier to represent the properties of multiple loosely related objects, allowing a single interface to be used to access these proprties.

## Overview
This project was created whilst testing various designs for modelling the properties of a collection of user interface widgets.

The idea is to use a token to uniquely identify any property among a collection of objects, in order to make the API used to access these properties as lightweight as possible.
For example, this could be achieved by using strings that descirbe the properties, but this is a lot less efficient, especially when mapping the string to an entry in the property store.

The PropertyToken contains two data members:
1. An enum identifying the object type
2. An integer representing the desired property (which is itself the index into a separate enum representing the available properties for this object)

NOTES
Each object-type provides a list of properties in an enum, and a mapping is created between them.

A special "common" object allows each object to share certain properties.

An API is also provided to generate a string representation of the proprties.

An example dataset is shown based on vehicle types. There are four concrete object types: car, plane, truck, bicycle, and these are all wrapped by a Vehicle class that uses type-erasure to set and get all of the properties.