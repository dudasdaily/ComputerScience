package web.diary;

import java.time.LocalDateTime;

import org.hibernate.annotations.CreationTimestamp;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class diary {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Integer no;
    public String title;
    public String content;
    @CreationTimestamp
    public LocalDateTime wdate;
}
