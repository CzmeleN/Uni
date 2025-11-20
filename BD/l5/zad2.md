# zad2

## denormalizacja 3NF
- dodajemy coś żeby mieć szybszy odczyt danych kosztem ich wielkości i aktualzacji/zapisu - unikamy kosztownych JOIN

- Patients
  - PatientID (PK)
  - FirstName
  - LastName
  - StreetAddress
  - ZipCode
  - City

- Physicians
  - PhysicianID (PK)
  - FirstName
  - LastName

- Appointments
  - AppointmentID (PK)
  - PatientID (FK -> Patients)
  - PhysicianID (FK -> Physicians)
  - PhysicianLastName // dodajemy nazwisko gdy chcemy np 
  - AppointmentDateTime
  - RoomNumber
  - Price
  - ServiceCategory
  - ServiceDescription

