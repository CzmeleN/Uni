# zad1

## 1NF
- każda komórka w tabeli musi zawierać tylko jedną wartość, nie może być zagnieżdżonych danych ani połączonych informacji

- Appointments:
  - LogID (PK)
  - PatientFirtName
  - PatientLastName
  - PatientStreet
  - PatientZipCode
  - PatientCity
  - AppointmentDateTime
  - RoomNumber
  - Price
  - PhysicianFirstName
  - PhysicianLastName
  - ServiceCategory
  - ServiceDescription

## 2NF
- każda kolumna w tabeli musi zależeć od całego klucza

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
  - AppointmentDateTime
  - RoomNumber
  - Price
  - ServiceCategory
  - ServiceDescription

## 3NF
- i tylko od klucza

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

- Services
  - ServiceID (PK)
  - Category
  - Desciption

- Appointments
  - AppointmentID (PK)
  - PatientID (FK -> Patients)
  - PhysicianID (FK -> Physicians)
  - ServiceID
  - AppointmentDateTime
  - RoomNumber
  - Price

