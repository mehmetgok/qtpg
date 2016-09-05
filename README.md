# qtpg

Example Qt and PostgreSQL connection

* This is command to create database **rtpq**


```sql
CREATE DATABASE rtpq
  WITH OWNER = postgres
       ENCODING = 'UTF8'
       TABLESPACE = pg_default
       LC_COLLATE = 'Turkish_Turkey.1254'
       LC_CTYPE = 'Turkish_Turkey.1254'
       CONNECTION LIMIT = -1;
```

* This is the command to create table

```sql
CREATE TABLE public.pqd
(
  id integer NOT NULL DEFAULT nextval('pqd_id_seq'::regclass),
  type integer NOT NULL,
  "time" timestamp without time zone,
  raw_data bytea,
  CONSTRAINT pqd_pkey PRIMARY KEY (id)
)
WITH (
  OIDS=FALSE
);
ALTER TABLE public.pqd
  OWNER TO postgres;
```