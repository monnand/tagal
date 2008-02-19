create table tags(id INTEGER PRIMARY KEY, tag TEXT UNIQUE, nr_ref INTEGER DEFAULT 0);
create table files(id INTEGER PRIMARY KEY, name TEXT, path TEXT UNIQUE);
create table tag_file_map(id INTEGER PRIMARY KEY, tid INTEGER, fid INTEGER);

insert into tags (tag) values ("tag1");
insert into tags (tag) values ("tag2");
insert into tags (tag) values ("tag3");

insert into files (name, path) values ("12", "/home/12");
insert into files (name, path) values ("32", "/home/32");

insert into tag_file_map (tid, fid) values (1,1);
update tags set nr_ref = nr_ref + 1 where id = 1;

insert into tag_file_map (tid, fid) values (2,1);
update tags set nr_ref = nr_ref + 1 where id = 2;

insert into tag_file_map (tid, fid) values (3,2);
update tags set nr_ref = nr_ref + 1 where id = 3;

insert into tag_file_map (tid, fid) values (2,2);
update tags set nr_ref = nr_ref + 1 where id = 2;

