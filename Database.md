```
/*������*/
create table if not exists `d_user`(
`id` bigint auto_increment comment '��������',
`account` VARCHAR(16) not null unique comment '�����˺���,Ψһ��',
`create_time` timestamp default current_timestamp() comment '����ʱ��',
`name` varchar(32) comment '�����',
`exp` bigint default 0 comment '����ֵ',
`lev` int unsigned default 0 comment '�ȼ�',
PRIMARY KEY (`id`)
)comment='�˻�ʱ���';
/*ɾ����*/
drop table `d_user`;

insert into `d_user`(account,name) values ("��־��","master");

insert into `d_user`(account,name) values ("lzc","master");


update `d_user` set `name`='master';

update `d_user` set account='ls',`name`='����',exp=2,lev=2 where id=1;

select * from `d_user`;

explain select * from `d_user` where `name`='��־��';
select * from `d_user`;
select * from d_user where account = '123';
```