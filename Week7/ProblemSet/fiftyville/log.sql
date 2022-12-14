-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Finding the IDs of the people at the crime scene on the particular day, and place
SELECT id, account_number FROM crime_scene_reports
WHERE street LIKE "Humphrey Street" AND month = 7 AND day = 28;

-- Finding more information about the crime that has happened
SELECT id, description FROM crime_scene_reports
WHERE street LIKE "Humphrey Street" AND month = 7 AND day = 28;

-- Finding out the interviews that happened on the crime day
SELECT name, transcript, id FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28;

-- Checking for why there are two eugene
SELECT name, id  FROM people
WHERE name LIKE "Eugene";

-- Seems like there is only one eugene, but two id in interviews
-- From the transcripts, it looks like only Eugene ID 162, Ruth ID 161 and Raymond ID 163 gave testimony relevant
-- to the case

-- It seems that the thief did one of three things
-- 1. He left the area ten minutes after thr theft. Got into a car and drove away
-- 2. Eugene ID 162 had recognized him at Leggett street withdrawing money
-- 3. Thief called someone for less than a minute, take the earliest flight out of fiftyville tomorrow.

-- Finding the people who withdrew money

--Finding the account number of people who withdrew money
SELECT account_number, amount
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';

-- Finding the names associated with the corresponding account numbers. Putting these names in the 'Suspect List'
SELECT name, atm_transactions.amount
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
  JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';


-- Finding the annonym of fiftyville in the flight plans
SELECT abbreviation FROM airports
WHERE city LIKE "Fiftyville";
-- SQL returns CSF

-- Finding the flight details
SELECT flights.id, full_name, city, flights.hour, flights.minute
FROM airports JOIN flights on airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = (SELECT id FROM airports
WHERE city LIKE "Fiftyville")
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute;
-- First flight out is from fiftyville to laguardia airport in NYC

-- Finding the destination_flight
SELECT full_name FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = 8
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour, flights.minute;

-- Now that we know the flight details, lets look at the passenger list
SELECT passengers.flight_id,name,passengers.seat, passengers.passport_number
FROM people JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE flights.year = 2021
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
AND flights.minute = 20
ORDER BY passengers.passport_number;

-- This is a list of potential suspects that flew on the flight
-- Checking the phone call records to find the person who bought the tickets.
-- Firstly, checking the possible names of the caller, and putting these names in the 'Suspect List'. Ordering them according to the durations of the calls.
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.caller
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
 ORDER BY phone_calls.duration;
-- Secondly, checking the possible names of the call-receiver. Ordering them according to the durations of the calls.
SELECT name, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE phone_calls.year = 2021
   AND phone_calls.month = 7
   AND phone_calls.day = 28
   AND phone_calls.duration <= 60
   ORDER BY phone_calls.duration;

-- Finding the license plate of the car
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.activity = "exit"
AND bakery_security_logs.minute >=15
AND bakery_security_logs.minute <=25
ORDER BY bakery_security_logs.minute;
-- These are the people that have left the bakery accourding to the testimony



--