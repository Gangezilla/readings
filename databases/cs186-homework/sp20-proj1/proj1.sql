DROP VIEW IF EXISTS q0, q1i, q1ii, q1iii, q1iv, q2i, q2ii, q2iii, q3i, q3ii, q3iii, q4i, q4ii, q4iii, q4iv, q4v;

-- Question 0
CREATE VIEW q0(era) 
AS
  SELECT MAX(era) FROM pitching;   -- replace this line
;

-- Question 1i
-- In the `people` table, find the `namefirst`, `namelast` and `birthyear` for all players with weight greater than 300 pounds.
CREATE VIEW q1i(namefirst, namelast, birthyear)
AS
  SELECT namefirst, namelast, birthyear
  FROM people
  WHERE weight > 300
;

-- Question 1ii
-- Find the `namefirst`, `namelast` and `birthyear` of all players whose `namefirst` field contains a space.
CREATE VIEW q1ii(namefirst, namelast, birthyear)
AS
  SELECT namefirst, namelast, birthyear
  FROM people
  WHERE namefirst ~ '\s'
;

-- Question 1iii
-- From the `people` table, group together players with the same `birthyear`, and report the `birthyear`, average `height`, and number of players for each `birthyear`. Order the results by `birthyear` in *ascending* order.
CREATE VIEW q1iii(birthyear, avgheight, count)
AS
  SELECT birthyear, avg(height) as avgheight, count(birthyear) as count
  FROM people
  GROUP BY birthyear
  ORDER BY birthyear ASC
;

-- Question 1iv
-- Following the results of Part iii, now only include groups with an average height > `70`. Again order the results by `birthyear` in *ascending* order.
CREATE VIEW q1iv(birthyear, avgheight, count)
AS
  SELECT birthyear, avg(height) as avgheight, count(birthyear) as count
  FROM people
  GROUP BY birthyear
  HAVING avg(height) > 70
  ORDER BY birthyear ASC
;

-- Question 2i
-- Find the `namefirst`, `namelast`, `playerid` and `yearid` of all people who were successfully inducted into the Hall of Fame in *descending* order of `yearid`.
CREATE VIEW q2i(namefirst, namelast, playerid, yearid)
AS
  SELECT p.namefirst, p.namelast, hof.playerid, hof.yearid
  FROM people p
  LEFT JOIN halloffame hof ON (hof.playerid = p.playerid)
  WHERE hof.inducted = 'Y'
  ORDER BY hof.yearid DESC
;

-- Question 2ii
CREATE VIEW q2ii(namefirst, namelast, playerid, schoolid, yearid)
AS
  SELECT p.namefirst, p.namelast, hof.playerid, sc.schoolid, hof.yearid
  FROM people p
  INNER JOIN halloffame hof ON (hof.playerid = p.playerid)
  INNER JOIN collegeplaying cp ON (p.playerid = cp.playerid)
  INNER JOIN schools sc ON (sc.schoolid = cp.schoolid)
  WHERE hof.inducted = 'Y' AND sc.schoolstate = 'CA'
  ORDER BY hof.yearid DESC, sc.schoolid ASC, hof.playerid ASC
;

-- Question 2iii
CREATE VIEW q2iii(playerid, namefirst, namelast, schoolid)
AS
  SELECT p.playerid, p.namefirst, p.namelast, hof.yearid, sc.schoolid
  FROM people p
  LEFT JOIN halloffame hof ON (hof.playerid = p.playerid)
  LEFT JOIN collegeplaying cp ON (p.playerid = cp.playerid)
  LEFT JOIN schools sc ON (sc.schoolid = cp.schoolid)
  WHERE hof.inducted = 'Y'
;
-- (b.h + (2 * b.h2b) )

-- Question 3i
CREATE VIEW q3i(playerid, namefirst, namelast, yearid, slg)
AS
  SELECT p.playerid, p.namefirst, p.namelast, b.yearid,
  (
    (b.h - b.h2b - b.h3b - b.hr + (2 * b.h2b) + (3 * b.h3b) + (4 * b.hr))
  / b.ab::float) slg
  FROM people p
  INNER JOIN batting b ON (p.playerid = b.playerid)
  WHERE b.ab > 50
  ORDER BY slg DESC, b.yearid ASC, p.playerid ASC 
  LIMIT 10
;
-- slugging percentage:
-- (batting.h + (2 * batting.h2b) + (3 * batting.h3b) + (4 * batting.hr)) / batting.ab
-- calculate slg for everyone in subquery
-- SELECT blah blah

-- Question 3ii
CREATE VIEW q3ii(playerid, namefirst, namelast, lslg)
AS
  SELECT 1, 1, 1, 1 -- replace this line
;

-- Question 3iii
CREATE VIEW q3iii(namefirst, namelast, lslg)
AS
  SELECT 1, 1, 1 -- replace this line
;

-- Question 4i
CREATE VIEW q4i(yearid, min, max, avg, stddev)
AS
  SELECT 1, 1, 1, 1, 1 -- replace this line
;

-- Question 4ii
CREATE VIEW q4ii(binid, low, high, count)
AS
  SELECT 1, 1, 1, 1 -- replace this line
;

-- Question 4iii
CREATE VIEW q4iii(yearid, mindiff, maxdiff, avgdiff)
AS
  SELECT 1, 1, 1, 1 -- replace this line
;

-- Question 4iv
CREATE VIEW q4iv(playerid, namefirst, namelast, salary, yearid)
AS
  SELECT 1, 1, 1, 1, 1 -- replace this line
;
-- Question 4v
CREATE VIEW q4v(team, diffAvg) AS
  SELECT 1, 1 -- replace this line
;

