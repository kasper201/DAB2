CREATE TABLE IF NOT EXISTS coureur (
                                       coureurID decimal(4,0) NOT NULL,
                                       naam varchar(20) NOT NULL,
                                       foto Blob NOT NULL,
                                       PRIMARY KEY (coureurID)
);

CREATE TABLE IF NOT EXISTS land (
                                    landID decimal(4,0) NOT NULL,
                                    naam varchar(60) NOT NULL,
                                    adjectival varchar(60) NOT NULL,
                                    PRIMARY KEY (landID)
);

CREATE TABLE IF NOT EXISTS landCoureur (
                                           ID decimal(4,0) NOT NULL,
                                           landID decimal(4,0) NOT NULL,
                                           coureurID decimal(4,0) NOT NULL,
                                           PRIMARY KEY (ID),
                                           KEY land (landID),
                                           KEY coureur (coureurID),
                                           CONSTRAINT fk_landCoureur_land FOREIGN KEY (landID) REFERENCES land(landID) ON UPDATE CASCADE,
                                           CONSTRAINT fk_landCoureur_coureur FOREIGN KEY (coureurID) REFERENCES coureur(coureurID) ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS circuit (
                                       ID decimal(4,0) NOT NULL,
                                       circuitNaam varchar(20) NOT NULL,
                                       lengte decimal(4,0) NOT NULL,
                                       landID decimal(4,0) NOT NULL,
                                       foto Blob NOT NULL,
                                       PRIMARY KEY (ID),
                                       KEY land (landID),
                                       CONSTRAINT fk_circuit_land FOREIGN KEY (landID) REFERENCES land(landID) ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS race (
                                    ID decimal(4,0) NOT NULL,
                                    circuitID decimal(4,0) NOT NULL,
                                    type varchar(20) NOT NULL,
                                    PRIMARY KEY (ID),
                                    KEY circuit (circuitID),
                                    CONSTRAINT fk_race_circuit FOREIGN KEY (circuitID) REFERENCES circuit(ID) ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS kalender (
                                        ID decimal(4,0) NOT NULL,
                                        raceID decimal(4,0) NOT NULL,
                                        datum date ,
                                        PRIMARY KEY (ID),
                                        KEY race(raceID),
                                        CONSTRAINT fk_kalender_race FOREIGN KEY (raceID) REFERENCES race(ID) ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS resultaat (
                                         resultaatID decimal(4,0) NOT NULL,
                                         raceID decimal(4,0) NOT NULL,
                                         score varchar(20) ,
                                         bestlap varchar(20) ,
                                         achievedIn integer ,
                                         position decimal(4,0) ,
                                         coureurID decimal(4,0) NOT NULL,
                                         PRIMARY KEY (resultaatID),
                                         KEY race (raceID),
                                         KEY coureur (coureurID),
                                         CONSTRAINT fk_resultaatCoureur_coureur FOREIGN KEY (coureurID) REFERENCES coureur(coureurID) ON UPDATE CASCADE,
                                         CONSTRAINT fk_resultaat_race FOREIGN KEY (raceID) REFERENCES race(ID) ON UPDATE CASCADE
);


CREATE TABLE IF NOT EXISTS team (
                                    ID decimal(4,0) NOT NULL,
                                    naam varchar(20) NOT NULL,
                                    PRIMARY KEY (ID)
);

CREATE TABLE IF NOT EXISTS teamCoureur (
                                           ID decimal(4,0) NOT NULL,
                                           teamID decimal(4,0) NOT NULL,
                                           coureurID decimal(4,0) NOT NULL,
                                           PRIMARY KEY (ID),
                                           KEY team (teamID),
                                           KEY coureur (coureurID),
                                           CONSTRAINT fk_teamCoureur_team FOREIGN KEY (teamID) REFERENCES team(ID) ON UPDATE CASCADE,
                                           CONSTRAINT fk_teamCoureur_coureur FOREIGN KEY (coureurID) REFERENCES coureur(coureurID) ON UPDATE CASCADE
);