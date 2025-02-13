package web.survey;

import java.time.LocalDateTime;

import org.hibernate.annotations.CreationTimestamp;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class survey {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Integer no;
    public String userid;
    public String artist;
    public String musician;
    @CreationTimestamp
    public LocalDateTime sdate;
}

