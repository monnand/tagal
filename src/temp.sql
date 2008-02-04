select distinct f.id, f.name, f.path from files as f, tag_file_map as map where f.id = map.fid 	and (select count(tid) from tag_file_map, tags where tid = tags.id and fid = map.fid and (tag = 'tag2' or tag = 'tag3')) = 2;

insert or ignore into tag_file_map (fid, tid) select f.id, t.id from files as f, tags as t where f.id = 3 and t.id = 4;
update tags set nr_ref=nr_ref-1 where tag='new one';

update tags set nr_ref=nr_ref-1 where id in (select t.id from tags as t, files as f, tag_file_map as m where f.id=m.fid and f.path='/home/32' and t.id=m.tid);
